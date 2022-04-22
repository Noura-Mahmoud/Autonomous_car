import React from 'react';
import { StyleSheet, Text, View, Button } from 'react-native';

import { useEffect, useState } from 'react';

let title = title

export default function Home(props) {

  let [Mode,setMode] = useState("")


    const select_mode= async(mode)=>{
        try{
          Mode=mode
          setMode(mode)
          if(mode=="Manual"){
            Manual(mode)}
      }
        catch(error){console.error(error)}}

      

      const Manual= async(mode)=>{
        try{
        console.log(title)
        // data = JSON.stringify({mode:"title" , direction:"none"})
        let response = await fetch('http://172.28.132.122:8090/video_feed', 
        { method: 'POST', headers: { Accept: 'application/json','Content-Type': 'application/json'},body: JSON.stringify({mode:mode , direction:"none"})
         
         });
         console.log(response)
        }
        catch(error){console.error(error)}}

  return (
      <>
    <Text style={styles.title}>Select Mode of driving car:</Text>
    <View style ={styles.container} >
    <Button 
      title= 'Manual Mode'
      onPress={() =>
       {select_mode('Manual');
    props.navigation.navigate("Manual Mode")
    }}
    />
        <Button style={styles.button1}
      title= 'Automatic Mode'
      onPress={() =>
       {select_mode('Automatic');
     props.navigation.navigate("Automatic Mode");
    }}
    />
  </View></>
  )
}


const styles = StyleSheet.create({

    container:
    {
        flex:1,
        display:"flex",
        justifyContent:'center',
        alignItems:'center',
        fontSize:30,
       
    },
    button1:
    {
        display:'flex',
        alignItems:'center',
        justifyContent:'center',
        marginTop:150,
        marginBottom:250,
        padding:3,

    },
    title:
    {   display:"flex",
        justifyContent:"center",
        alignItems:"flex-start",
        fontSize:30,
        fontWeight:'100',
        marginTop:60
        

    }
});