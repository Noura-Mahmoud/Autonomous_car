import React, { Component } from 'react';
import { Text, View,StyleSheet,Button } from "react-native";
import { TouchableHighlight,TouchableOpacity } from 'react-native';
import Icon from 'react-native-vector-icons/AntDesign';
export default function ManualMode() {
    let data=[]
    async function send_mode(dir){
    
 
        let response = await fetch('http://172.28.132.122:8090/video_feed', 
        { method: 'POST', headers: { Accept: 'application/json','Content-Type': 'application/json'},body: JSON.stringify({mode:"Manual" , direction:dir})
         });
        
        }
  return (
  <View style={styles.all} >
<View style={styles.buttonRight}>
 <Text style={styles.button}> <Icon.Button name="caretright"  style={styles.button} onPress={()=>{send_mode("R")}}></Icon.Button></Text></View>
 <View style={styles.buttonLeft}>
 <Text style={styles.button}> <Icon.Button name="caretleft"  style={styles.button} onPress={()=>{send_mode("L")}}></Icon.Button></Text></View>
 <View style={styles.buttonUp}>
 <Text style={styles.button}> <Icon.Button name="caretup"  style={styles.button} onPress={()=>{send_mode("F")}}></Icon.Button></Text></View>
 <View style={styles.buttonDown}>
 <Text style={styles.button}> <Icon.Button name="caretdown"  style={styles.button} onPress={()=>{send_mode("B")}}></Icon.Button></Text></View>
</View>
  )
}


const styles = StyleSheet.create({
button:
    {
    
        justifyContent: "center",
        alignItems: "center",
        paddingVertical: 15,
        paddingHorizontal: 3,
        elevation: 2,
        paddingLeft:10,

        
    },
buttonRight:
{

    justifyContent: "center",
    alignItems: "center",
    paddingVertical: 15,
    paddingHorizontal: 3,
    elevation: 2,
    paddingLeft:10,
    marginLeft:180,
    marginTop:60
    
},
buttonUp:
{

    justifyContent: "center",
    alignItems: "center",
    paddingVertical: 15,
    paddingHorizontal: 3,
    elevation: 2,
    paddingLeft:10,
    marginLeft:-12,
    marginTop:-220
    
},
buttonLeft:
{

    justifyContent: "center",
    alignItems: "center",
    paddingVertical: 15,
    paddingHorizontal: 3,
    elevation: 2,
    paddingLeft:10,
    marginTop:-115,
    marginLeft:-200
    
    
},
buttonDown:
{

    justifyContent: "center",
    alignItems: "center",
    paddingVertical: 15,
    paddingHorizontal: 3,
    elevation: 2,
    paddingLeft:10,
    marginTop:100,
    marginLeft:-12
    
    
},
all:
{
    marginTop:140,
    justifyContent: "center",
    alignItems: "center",
    paddingVertical: 15,
    paddingHorizontal: 3,
    elevation: 2,
    paddingLeft:10,
    
    
},
});
