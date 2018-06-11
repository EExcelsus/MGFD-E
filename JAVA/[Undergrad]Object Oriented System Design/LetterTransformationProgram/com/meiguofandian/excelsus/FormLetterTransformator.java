package com.meiguofandian.excelsus;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.Scanner;

public class FormLetterTransformator {
	private static String[] workString;
	
	private static KeyValue[] keyArray;
	private static int currentCount=0;
	
	private static void processKey() {
		for(int ids = 0; ids < workString.length;ids++) {
			for(int idi = 0; idi < keyArray.length;idi++) {
				//ASK!r
				workString[ids] = workString[ids].replaceAll("\\{"+keyArray[idi].getKey()+"\\}", keyArray[idi].getValue());
			}
		}
	}
	
	private static void produceKey(String nextLineOfToken) {
		keyArray[currentCount++]=new KeyValue(nextLineOfToken);
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		// File Input / output stream init
		PrintWriter fileOutput = null;
		
		Scanner fileTemplate =null;
		Scanner fileProperties =null;

		try {
			//Scanning for number of KeyValues needed
			int lines=0;
			
			fileProperties = new Scanner(new FileInputStream("properties.txt"));
			while(fileProperties.hasNextLine()) {
				lines++;
				fileProperties.nextLine();
			}
			
			//Initializing Array
			keyArray=new KeyValue[lines];
			lines =0;
			
			//Scanning for number of Strings needed
			fileTemplate = new Scanner(new FileInputStream("template_file.txt"));
			while(fileTemplate.hasNextLine()) {
				lines++;
				fileTemplate.nextLine();
			}
			
			//Initializing Array
			workString = new String[lines];
			
			//Close the File
			if (fileTemplate != null)
				fileTemplate.close();
			if (fileProperties != null)
				fileProperties.close();
			
			//Loading Template
			fileTemplate = new Scanner(new FileInputStream("template_file.txt"));
			while(fileTemplate.hasNextLine()) {
				workString[currentCount++]=fileTemplate.nextLine();
			}
			
			currentCount =0;
			
			//Loading KeyValues
			fileProperties = new Scanner(new FileInputStream("properties.txt"));
			while(fileProperties.hasNextLine()) {
				produceKey(fileProperties.nextLine());
			}

			//Using Keys on the template
			processKey();
			
			//Output
			fileOutput = new PrintWriter(new FileOutputStream("output_file.txt"));
			for(int idi =0;idi<workString.length;idi++) {
				fileOutput.println(workString[idi]);
			}
		} catch (Exception e) {
			//handle exception
			e.printStackTrace();
		} finally {
			try {
				// close input / output stream
				if (fileOutput != null)
					fileOutput.close();
				if (fileTemplate != null)
					fileTemplate.close();
				if (fileProperties != null)
					fileProperties.close();
			} catch (Exception e2) {
				// handle exception
				e2.printStackTrace();
			}
		}
	}

}
