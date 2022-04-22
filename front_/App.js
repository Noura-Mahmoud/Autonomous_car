import React, { Component } from 'react';
import { Text, View,StyleSheet,Button } from "react-native";

import 'react-native-gesture-handler';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';
import ManualMode from './Components/ManualMode';
import Home from './Components/Home';
import AutoMode from './Components/AutoMode';
const Stack = createStackNavigator();
export default function App() {

  return (
      <NavigationContainer>
        <Stack.Navigator>
        <Stack.Screen
            name="Self Driving Car"
            component={Home}
          />
          <Stack.Screen
            name="Manual Mode"
            component={ManualMode}
          />
                    <Stack.Screen
            name="Automatic Mode"
            component={AutoMode}
          />
        </Stack.Navigator>
      </NavigationContainer>

  )
}




