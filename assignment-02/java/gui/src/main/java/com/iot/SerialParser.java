package com.iot;
import java.io.BufferedReader;
import java.io.Console;
import java.io.InputStreamReader;

import com.iot.SerialCommChannel;

public class SerialParser  {
	SerialCommChannel ch;

	public SerialParser(String port, int rate) throws Exception{
		ch = new SerialCommChannel(port,rate);
	}

	protected SerialCommChannel getChannel() throws Exception{
		if(ch==null){
			throw new Exception("Communication channel does not exists");
		}else{
			return ch;
		}
	}
	   


	
    
}