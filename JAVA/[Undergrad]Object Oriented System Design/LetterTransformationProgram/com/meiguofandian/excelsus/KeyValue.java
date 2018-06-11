package com.meiguofandian.excelsus;

import java.util.StringTokenizer;

public class KeyValue {
	// ������Ƽ
	public String getKey() {
		return m_key;
	}

	public String getValue() {
		return m_value;
	}

	// ��� ����
	private String m_key;
	private String m_value;

	// ������
	public KeyValue(String key, String value) {
		this.m_key = key;
		this.m_value = value;
	}

	public KeyValue(String tokenString) {
		StringTokenizer tokenizer = new StringTokenizer(tokenString, "=");

		if (tokenizer.countTokens() == 2) {
			this.m_key = tokenizer.nextToken();
			this.m_value = tokenizer.nextToken();
		} else {
			System.out.println("Property Token String Invalid.");
		}
	}
}
