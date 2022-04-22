import React from 'react'
import { View,Text } from 'react-native';
import { StyleSheet ,BackHandler,Alert ,RCTAnimation} from 'react-native';
import { useEffect, useState } from 'react';


export default function AutoMode() {
  let [sec,setSec]=useState(0)

  var refresh=setInterval(() => {
    setSec(sec+=1)
  }, 1000);

  const send_mode= async(mode)=>{
    try{
      if(mode=="Automatic"){
      let response = await fetch('http://172.28.132.122:8090/video_feed', 
      { method: 'POST', headers: { Accept: 'application/json','Content-Type': 'application/json'},body: JSON.stringify({mode:mode , direction:"none"})
     
     });
    }
  }
    catch(error){console.error(error)}}
    useEffect(()=>{send_mode("Automatic"),[sec]})
    useEffect(()=>{return()=>{
      clearInterval(refresh)
    }})

    const backAction = () => {
      console.log("back")
      Alert.alert("Hold on! Are you sure you want to go back?")
    };

    const backHandler = BackHandler.addEventListener(
      "hardwareBackPress",
      backAction
    );

  return (


    <Text style={styles.container}>Open IP webcam App to begin Capturing images</Text>
  )
}


const styles = StyleSheet.create({

    container:
    {
        flex:1,
        display:"flex",
        justifyContent:'center',
        alignItems:'center',
        fontSize:30
    }
});