# -*- coding: utf-8 -*-
"""
Created on Mon Apr  3 02:23:50 2017

@author: root
"""

from pymote.algorithm import NodeAlgorithm
from pymote.message import Message


class TestSpanningTree(NodeAlgorithm):
    required_params = {}
    default_params = {'neighborsKey' : 'Neighbors'}
    
    def initializer(self):
        for node in self.network.nodes():
            #Ocitali smo sve susjede - svi znaju sve svoje susjede
            node.memory[self.neighborsKey] = \
                node.compositeSensor.read()['Neighbors']           
            #Set all nodes to idle state  
            node.status = 'IDLE'

        ini_node = self.network.nodes()[0]
        ini_node.status = 'INITIATOR'

        self.network.outbox.insert(0, Message(header = NodeAlgorithm.INI,
                                              destination = ini_node))
        
    def initiator(self, node, message):
        if message.header == NodeAlgorithm.INI:
            node.memory['root'] = 'True'
            node.memory['counter'] = 0
            node.memory['tree'] = []
            node.memory['neigh'] = len(node.memory[self.neighborsKey])
            node.send(Message(header = 'Q',
                    destination = node.memory[self.neighborsKey]))
            node.status = 'ACTIVE'

    def idle(self, node, message): 
        if message.header == 'Q':
            tree = []
            node.memory['root'] = 'False'
            node.memory['parent'] = message.source
            
            tree.append(message.source)
            node.memory['tree'] = list(tree)
            node.memory['neigh'] = len(node.memory[self.neighborsKey])
            
            node.send(Message(header = 'Yes', destination = message.source))
            node.memory['counter'] = 1
            if node.memory['counter'] == node.memory['neigh']:
                node.status = 'DONE'
            else:
                node.memory['N_P'] = list(node.memory[self.neighborsKey])
                node.memory['N_P'].remove(node.memory['parent'])
                node.send(Message(header = 'Q',
                                destination = node.memory['N_P']))
                node.status = 'ACTIVE'
        
    def active(self, node, message):
        if message.header == 'Q':
            node.send(Message(header = 'No',
                    destination = message.source))
        elif message.header == 'Yes':
            node.memory['tree'].append(message.source)
            node.memory['counter'] = node.memory['counter'] + 1
            if node.memory['counter'] == node.memory['neigh']:
                node.status = 'DONE'
        else:
            node.memory['counter'] = node.memory['counter'] + 1
            if node.memory['counter'] == node.memory['neigh']:
                node.status = 'DONE'

    
    def done(self, node):
        pass

    
    STATUS = {
            'INITIATOR' : initiator,
            'ACTIVE'   : active,
            'IDLE'      : idle, 
            'DONE'      : done,
            }
            
class Saturation(TestSpanningTree):
    # Start node
    def initializer(self):
        for node in self.network.nodes():          
            node.status = 'AVAILABLE'
            node.memory['newTree'] = list(node.memory['tree'])
            node.memory[self.neighborsKey] = \
                node.compositeSensor.read()['Neighbors']  
        ini_node = self.network.nodes()[0]
        self.network.outbox.insert(0, Message(header = 'Start',
                                              destination = ini_node))
        
    def available(self, node, message):     
        # Only start node will enter here
        if message.header == 'Start':                      
            self.initialize(node, message)  
            self.prepareMessage(node, message)
            
            # Send ACTIVATE message for all neighbors
            node.send(Message(header = 'Activate',
                    destination = node.memory[self.neighborsKey]))
            node.status = 'ACTIVE'            

            """ RECEIVING nodes """
        elif message.header == 'Activate':
            self.initialize(node, message)
     
            destination_nodes = list(node.memory['tree'])
            # Remove sender
            destination_nodes.remove(message.source)
            # Send message
            node.send(Message(header = 'Activate',
                    destination = destination_nodes))
                        
            # Check if this is Leaf
            if len(destination_nodes) == 0:
                data = self.prepareMessage(node, message)
                
                # Send response to parent
                node.send(Message(header = 'M',
                    destination = node.memory['parent'],
                    data = data))
                node.status = 'PROCESSING'
            else:
                node.status = 'ACTIVE'
              
    def active(self, node, message):     
        # This is not the root
        #if node.memory['root'] != 'True': 
        if message.header == 'M':
            self.processMessage(node, message)

            dest_nodes = list(node.memory['newTree'])
            dest_nodes.remove(message.source)
            node.memory['Neighbors'].remove(message.source)                
            
            # Check if this is Leaf or if all neighbors returned message
            if len(node.memory['Neighbors']) == 1:
                # Send response to parent
                data = self.prepareMessage(node, message)
                node.send(Message(header = 'M',
                        destination = node.memory['parent'],
                        data = data))
            
                node.status = 'PROCESSING'
        """      
        else:
           if message.header == 'M':
               self.processMessage(node, message)
               dest_nodes = list(node.memory['newTree'])
               dest_nodes.remove(message.source)

               # Check if this is Leaf or if all neighbors returned message
               if len(dest_nodes) == 0:
                    data = self.prepareMessage(node, message)
                    
                    node.send(Message(header = 'M',
                                destination = node.memory['parent'],
                                data = data))
                    node.status = 'PROCESSING'
        """   

    def processing(self, node, message):
        # Full Saturation implementation
        if message.header == 'M':
            self.processMessage(node, message)
            self.resolve(node, message)

    def saturated(self, node, message):
        pass
    
    #Procedure    
    def initialize(self, node, message):
        pass
     
    #Procedure
    def prepareMessage(self, node, message):  
        m = ['Saturation']
    
    #Procedure
    def resolve(self, node, message):
        node.status = 'SATURATED'
    
    #Procedure
    def processMessage(self, node, message):
        pass
       
    
    STATUS = {
            'AVAILABLE' : available,
            'ACTIVE' : active,
            'PROCESSING' : processing,
            'SATURATED' : saturated
    }
    
    
    
class Eccentricities(Saturation):
    def processing(self, node, message):
        if message.header == 'Resolution':
            self.resolve(node, message)
    
    def done(self, node, message):
        pass
    
    #Procedure
    def initialize(self, node, message):
        node.memory['distance'] = { }
        for i in node.memory['tree']:
            node.memory['distance'][i] = 0
        
    #Procedure
    def prepareMessage(self, node, message):
        return 1 + max(list(node.memory['distance'].values()))
        
    #Procedure
    def resolve(self, node, message):
        self.processMessage(node, message)
        self.calculateEccentricity(node, message)
        
        for i in list(node.memory['tree']):
            #Check if it is for parent
            if i == node.memory['parent']:
                pass
            else:
                distances = dict(node.memory['distance'])
                distances.pop(i, None)
                max_dist = 1 + max(list(distances.values()))
                node.send(Message(header = 'Resolution',
                                  destination = i,
                                  data = max_dist))
        
        node.status = 'DONE'
        
    #Procedure
    def processMessage(self, node, message):
        node.memory['distance'][message.source] = message.data
        
    #Procedure
    def calculateEccentricity(self, node, message):
        node.memory['eccentricity'] = max(list(node.memory['distance'].values()))
        
    STATUS = {
        'AVAILABLE' : Saturation.STATUS.get('AVAILABLE'),
        'ACTIVE' : Saturation.STATUS.get('ACTIVE'),
        'PROCESSING': processing,
        'SATURATED' : Saturation.STATUS.get('SATURATED'),
        'DONE' : done
    }
        
class Center(Eccentricities):
    def processing(self, node, message):
        if message.header == 'Center':
            self.resolve(node, message)
    
    def done(self, node, message):
        pass
    
    #Procedure
    def initialize(self, node, message):
        node.memory['maxValue'] = 0
        node.memory['max2Value'] = 0
    
    #Procedure
    def prepareMessage(self, node, message):
        return node.memory['maxValue'] + 1
    
    #Procedure
    def processMessage(self, node, message):
        received_data = message.data
        if node.memory['maxCounter'] < received_data:
            node.memory['max2Value'] = node.memory['maxValue']
            node.memory['maxValue'] = received_data
            node.memory['maxNeighbor'] = message.source
        else:
            if node.memory['max2Value'] < received_data:
                node.memory['max2Value'] = received_data
    
    #Procedure
    def resolve(self, node, message):
        max_value = node.memory['maxValue']
        max2_value = node.memory['max2Value']
        if (max_value - max2_value) == 1:
            if node.memory['maxNeighbor'] != node.memory['parent']:
                node.send(Message(header = 'Center',
                                  destination = node.memory['maxNeighbor'],
                                  data = max2_value))
                node.status = 'CENTER'
        else:
            if (max_value - max2_value) > 1:
                node.send(Message(header = 'Center',
                                  destination = node.memory['maxNeighbor'],
                                  data = max2_value))
            else:
                node.status = 'CENTER'
    
    STATUS = {
        'AVAILABLE' : Saturation.STATUS.get('AVAILABLE'),
        'ACTIVE' : Saturation.STATUS.get('ACTIVE'),
        'PROCESSING': processing,
        'SATURATED' : Saturation.STATUS.get('SATURATED'),
        'DONE' : done     
    }