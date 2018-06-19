package com.meiguofandian.excelsus;

public interface Voter extends Comparable<Voter>{
	public abstract int vote(int numberOfCandidates);
}
