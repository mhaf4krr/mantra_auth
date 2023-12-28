import React, { useContext, useEffect, useState } from "react";

import StageContext from "../context/StageContext";

import FingerIdle from "../assets/scanning.gif";
import FingerScanning from "../assets/scanning_finger.gif";

import { socket } from "../utils/socket";

import { Container, ProgressBar} from "react-bootstrap"

export default function FingerScanAnimation() {
  const stageContext = useContext(StageContext);

  const [scannedImage,setScannedImage] = React.useState<null | string>(null)
  const [scanQuality,setScanQuality] = React.useState<number>(0)

  useEffect(()=>{
    socket.on("fingerprint_image_client",(imageData:string)=>{
      setScannedImage(imageData)
    })

     socket.on("finger_scan_quality_progress",(quality)=>{
      console.log({quality})

      if(quality != scanQuality){
        setScanQuality(quality)
      }
    
    })
  },[])



  function AnimationPerStage(stage: string) {

    if(stage === "SCANNING_FINGER" && scannedImage!=null){
      return scannedImage
    }

    switch (stage) {
      case "IDLE":
        return FingerIdle;
        break;
      case "SCANNING_FINGER":
        return FingerScanning;
        break;

      default:
        return FingerIdle;
    }
  }

  return (
    <section className="text-center">
      <img
        src={AnimationPerStage(stageContext.stage)}
        width={"50%"}
        height={"auto"}
      />

      {stageContext.stage === "SCANNING_FINGER" && <div className="py-3 px-3">
        <ProgressBar role="progressbar" variant="success" striped animated now={scanQuality} label={`SCANNING FINGER QUALITY: ${scanQuality}`} min={0} max={73}/>
      </div>}
      <hr />
      <h6>FINGER SCANNER</h6>
    </section>
  );
}
