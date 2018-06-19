package com.meiguofandian.excelsus;

public class Candidate extends Student{
	private int voteReceived;
	
	public Candidate(int id, Department department, String name) {
		super(id,department,name);
		voteReceived = 0;
	}
	
	public void voteIncrease() {
		voteReceived++;
	}
	
	public int getVote() {
		return voteReceived;
	}
	
	@Override
	public int compareTo(Voter obj) {
		if (obj == null) throw new NullPointerException("Object is null"); 
		if (!this.getClass().equals(obj.getClass())) 
			throw new ClassCastException("Object not of the same type"); 
		Candidate toCompare = (Candidate) obj; 
		if (this.voteReceived > toCompare.voteReceived) return -1; 
		if (this.voteReceived == toCompare.voteReceived) return 0; 
		else 
			return 1;
	}
}
