package com.meiguofandian.excelsus;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;

public class Department {
	private String name;
	private ArrayList<Candidate> candidate;
	private ArrayList<Student> student;

	public Department(String name) {
		this.name = name;

		candidate = new ArrayList<Candidate>();
		student = new ArrayList<Student>();
	}

	public void addStudent(Student student, String isCandidate) {
		if (isCandidate.equals("TRUE")) {
			this.candidate.add((Candidate) student);
		}
		this.student.add(student);
	}

	public Candidate callAllVote() {
		if(candidate.size()==0) {
			System.out.println("There is no candidate for "+this.name+"!");
			return null;
		}
		
		Iterator<Student> iterator = student.iterator();
		while (iterator.hasNext()) {
			Student element = iterator.next();
			candidate.get(element.vote(candidate.size())).voteIncrease();
		}

		Collections.sort(candidate);
		return candidate.get(0);
	}

	public String getName() {
		return name;
	}
}
