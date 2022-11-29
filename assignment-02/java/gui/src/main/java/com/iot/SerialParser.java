package com.iot;

import java.util.ArrayList;

public class SerialParser {

	public SerialParser() throws Exception {
	}

	public ArrayList<Float> getNewChartData(ArrayList<String> rawSerial) {

		ArrayList<Float> data = new ArrayList<>();
		for (String item : rawSerial) {
			String[] parts = item.split("-");
			parts[0].trim();
			parts[0].toLowerCase();
			if (parts[0].equals(("waterlevel"))) {
				if (parts[1] != "")
					data.add(Float.parseFloat(parts[1]));
			}
		}
		return data;
	}

	public String getState(ArrayList<String> rawSerial, String preValString) {

		String[] msg;
		// inversed read of data to take only the last state
		for (int i = rawSerial.size() - 1; i > 0; i--) {
			msg = rawSerial.get(i).split("-");
			msg[0].trim();
			msg[0].toLowerCase();
			if (msg[0].equals("state")) {
				return msg[1];
			}
		}
		return preValString;
	}

	public String getSmartLight(ArrayList<String> rawSerial, String preValString) {
		String[] msg;

		// inversed read of data to take only the last state
		for (String item : rawSerial) {
			msg = item.split("-");
			msg[0].trim();
			msg[0].toLowerCase();
			if (msg[0].equals("smartlight")) {
				return msg[1];
			}
		}
		return preValString;
	}

	public float getServoPosition(ArrayList<String> rawSerial) {
		float pos = 360;
		String[] msg;
		// inversed read of data to take only the last opening of the valve
		for (int i = rawSerial.size() - 1; i > 0; i--) {
			msg = rawSerial.get(i).split("-");
			System.out.print(msg.length);
			msg[0].trim();
			msg[0].toLowerCase();
			if (msg[0] == "servo") {
				pos = Float.parseFloat(msg[1].toString());
				return pos;
			}
		}
		return 0;
	}

}