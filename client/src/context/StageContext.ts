import { useState, createContext, Dispatch, SetStateAction } from "react";
import ReactDOM from "react-dom/client";



interface StageContextInterface {
    stage: string;
    setStage: Dispatch<SetStateAction<string>>
  }

const StageContext = createContext<StageContextInterface>({
    stage:"IDLE",
    setStage:()=>{}
})

export default StageContext