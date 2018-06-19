package com.meiguofandian.excelsus;

import java.util.Random;

public class Student implements Voter{
	private String name;
	private int id;
	//private int grade;
	private Department department;
	
	public Student(int id, Department department, String name) {
		this.id = id;
		this.department=department;
		this.name = name;
	}

	@Override
	public int vote(int numberOfCandidates){
		Random tempRandom = new Random();
		return tempRandom.nextInt(numberOfCandidates);
	}

	@Override
	public int compareTo(Voter obj) {
		if (obj == null) throw new NullPointerException("Object is null"); 
		if (!this.getClass().equals(obj.getClass())) 
			throw new ClassCastException("Object not of the same type"); 
		Student toCompare = (Student) obj; 
		if (this.id > toCompare.id) return -1; 
		if (this.id == toCompare.id) return 0; 
		else 
			return 1;
	}
	
	public Department getDepartment() {
		return this.department;
	}
	
	public String getName() {
		return this.name;
	}
	
	public int getId() {
		return this.id;
	}
}
