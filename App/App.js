import React from 'react';
import { useEffect, useState } from 'react';
// import "bootstrap/dist/css/bootstrap.min.css";
// import { Button } from 'react-native-web';
// import { Button } from "react-bootstrap";
import axios from "axios";


export default function App() {

  let [sec,setSec]=useState(0)
  let data =[]
  setInterval(() => {
    setSec(sec+=1)
  }, 300000);
  
  async function send_mode(){
    data = JSON.stringify({mode:"Automatic" , direction:"none"})
    axios.post(`http://192.168.1.5:8090//video_feed`, data ,{headers:{ "Content-Type":'application/json'}})
    .then(res => {
      // structurd data stored in index 2 of data 
      console.log(res.data);
    })
  }

 
  useEffect(()=>send_mode(),[sec])

  return (
    <div>
      <button onClick={()=>{send_mode()}}>press</button>
      </div>
  );
}
