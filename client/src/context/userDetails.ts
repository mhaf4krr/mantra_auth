import { useState, createContext, Dispatch, SetStateAction } from "react";
import ReactDOM from "react-dom/client";



interface userDetailsInterface {
    rollNumber: string;
    setRollNumber: Dispatch<SetStateAction<string>>,
    userIdentified:boolean,
    setUserIdentified:Dispatch<SetStateAction<boolean>>,
  }

const UserContext = createContext<userDetailsInterface>({
   rollNumber: "",
     setRollNumber:()=>{}, 
    userIdentified:false,
    setUserIdentified:()=>{}
})

export default UserContext