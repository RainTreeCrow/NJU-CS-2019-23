int judgeStringType(char* s1, char* s2) {
	int i, l1, l2, temp;
	bool eq2 = true, eq3 = true, eq4 = true;
	for (l1 = 0; s1[l1] != '\0'; l1++);
	for (l2 = 0; s2[l2] != '\0'; l2++);
	if (l1 != l2)
		return 1;
	for (i = 0; s1[i] != '\0'; i++) {
		if (s1[i] != s2[i])
			eq2 = false;
		if (s1[i] != s2[i] && s1[i] != s2[i] + 32 && s1[i] != s2[i] - 32)
			eq3 = false;
	}
	if (eq2)
		return 2;
	if (eq3)
		return 3;
	temp = (s2[0] + 26 - s1[0]) % 26;
	for (i = 0; s1[i] != '\0'; i++) {
		if (((s2[i] + 26 - s1[i]) % 26) != temp) {
			eq4 = false;
			break;
		}
	}
	if (temp > 0 && eq4)
		return 4;
	return 5;
}