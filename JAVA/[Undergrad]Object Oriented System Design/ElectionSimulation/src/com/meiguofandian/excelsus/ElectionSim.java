package com.meiguofandian.excelsus;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.Scanner;
import java.util.StringTokenizer;

public class ElectionSim {
	private String DEPARTMENT_INPUT_FILE_PATH;
	private String STUDENT_INPUT_FILE_PATH;
	private String OUTPUT_FILE_PATH;

	private ArrayList<Department> department;
	private ArrayList<Candidate> candidate;

	public ElectionSim(String depIn, String stuIn, String output) {
		this.DEPARTMENT_INPUT_FILE_PATH = depIn;
		this.STUDENT_INPUT_FILE_PATH = stuIn;
		this.OUTPUT_FILE_PATH = output;
		
		this.department = new ArrayList<Department>();
		this.candidate = new ArrayList<Candidate>();

		Scanner fileDepartment = null;
		Scanner fileStudent = null;

		// TODO: Read Files
		try {
			fileDepartment = new Scanner(new FileInputStream(this.DEPARTMENT_INPUT_FILE_PATH));

			if (!fileDepartment.hasNext())
				throw new FileNotFoundException("File blank!");
			else
				fileDepartment.nextLine();
			
			//Fake Department to match the index number and real number
			this.department.add(new Department("School"));

			while (fileDepartment.hasNext())
				instantiate(fileDepartment.nextLine(), 0);

			fileDepartment.close();

			fileStudent = new Scanner(new FileInputStream(this.STUDENT_INPUT_FILE_PATH));

			if (!fileStudent.hasNext())
				throw new FileNotFoundException("File blank!");
			else
				fileStudent.nextLine();
			
			while (fileStudent.hasNext())
				instantiate(fileStudent.nextLine(), 1);

			fileStudent.close();

		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				if (fileDepartment != null)
					fileDepartment.close();
				if (fileStudent != null)
					fileStudent.close();
			} catch (Exception e2) {
				e2.printStackTrace();
			}
		}
	}

	private void instantiate(String nextLineOfToken, int classType) {
		try {
			StringTokenizer tokenizer = new StringTokenizer(nextLineOfToken, ",");
			
			// Department Creation
			if (classType == 0 && tokenizer.countTokens() == 2) {
				tokenizer.nextToken();
				this.department.add(new Department(tokenizer.nextToken()));
			}

			// Student Creation
			else if (classType == 1 && tokenizer.countTokens() == 4) {
				String tokens[] = new String[4];
				for (int idi = 0; idi < 4; idi++) {
					tokens[idi] = tokenizer.nextToken();
				}
				
				Student tempStudent;
				if (tokens[3].equals("TRUE")) {
					tempStudent = new Candidate(Integer.parseInt(tokens[0]),
							department.get(Integer.parseInt(tokens[1])), tokens[2]);
				} else {
					tempStudent = new Student(Integer.parseInt(tokens[0]), department.get(Integer.parseInt(tokens[1])),
							tokens[2]);
				}
				department.get(Integer.parseInt(tokens[1])).addStudent(tempStudent, tokens[3]);
			}
			// Token Size Invalid
			else {
				throw new FileNotFoundException("Token Length Invalid!");
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
		}
	}

	public void runSimulation() {
		Iterator<Department> iterator = department.iterator();
		//The "0" Department must be skipped
		iterator.next();
		while(iterator.hasNext()) {
			Candidate tempCandidate = iterator.next().callAllVote();
			if(tempCandidate != null)
				candidate.add(tempCandidate);
		}
		saveData();
	}

	private void saveData() {
		PrintWriter fileOutput = null;
		
		try {
			Collections.sort(candidate);
			
			fileOutput=new PrintWriter(new FileOutputStream(this.OUTPUT_FILE_PATH));
			Iterator<Candidate> iterator = candidate.iterator();
			while(iterator.hasNext()) {
				Candidate element = iterator.next();
				fileOutput.println("======== Elected Candidate ========");
				fileOutput.println("Department name: "+element.getDepartment().getName());
				fileOutput.println("name: "+element.getName());
				fileOutput.println("Student_id: "+element.getId());
				fileOutput.println("Votes: "+ element.getVote());
				fileOutput.println("===================================");
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				if (fileOutput != null)
					fileOutput.close();
			} catch (Exception e2) {
				e2.printStackTrace();
			}
		}
	}
}
