#include"main.h"
//�û�ע��
void registerUser() {
	char id[20], username[20], role[20], account[20], password[20];
	cout << "������ID��" << endl;
	cin >> id;
	cout << "�������û�����" << endl;
	cin >> username;
	cout << "�������ɫ��������/ѧ������" << endl;
	cin >> role;
	cout << "�������˺ţ�" << endl;
	cin >> account;
	cout << "���������룺" << endl;
	cin >> password;

	// ���ݽ�ɫ���벻ͬ���ļ�
	if (strcmp(role, "ѧ��") == 0) {
		ofstream studentFile("students.csv", ios::app);
		studentFile << id << "," << username << "," << role << "," << account << "," << password << endl;
		studentFile.close();
		num_students++;  // ����ѧ������
	}
	else if (strcmp(role, "������") == 0) {
		ofstream principalFile("principals.csv", ios::app);
		principalFile << id << "," << username << "," << role << "," << account << "," << password << endl;
		principalFile.close();
		num_principal++;  // ���¸���������
	}
	else {
		cout << "��ɫ�������������'������'��'ѧ��'��" << endl;
	}
}



//�����û���Ϣ
void loadUsersFromFile() {
	ifstream file("users.csv");
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string field;
		vector<string> fields;

		while (getline(ss, field, ',')) {
			fields.push_back(field);
		}

		strcpy(users[num_users].id, fields[0].c_str());
		strcpy(users[num_users].username, fields[1].c_str());
		strcpy(users[num_users].role, fields[2].c_str());
		strcpy(users[num_users].account, fields[3].c_str());
		strcpy(users[num_users].password, fields[4].c_str());

		num_users++;
	}

	file.close();
}

//���ѧ����Ϣ

void addStudent() {
	if (num_students >= MAX_Users) {
		cout << "�Ѵﵽ���ѧ���������޷�����µ�ѧ��" << endl;
		return;
	}

	Student newStudent;
	cout << "������ѧ��ID��" << endl;
	cin >> newStudent.id;
	cout << "������ѧ�����ƣ�" << endl;
	cin >> newStudent.name;
	cout << "������ѧ�����룺" << endl;
	cin >> newStudent.password;
	strcpy(newStudent.role, "ѧ��");

	students[num_students] = newStudent;
	num_students++;
}


//ɾ��ѧ����Ϣ
void deleteStudent() {
	char id[20];
	cout << "������Ҫɾ����ѧ��ID��" << endl;
	cin >> id;

	int i;
	for (i = 0; i < num_students; i++) {
		if (strcmp(students[i].id, id) == 0) {
			break;
		}
	}

	if (i < num_students) {
		for (int j = i; j < num_students - 1; j++) {
			students[j] = students[j + 1];
		}
		num_students--;
	}
	else {
		cout << "δ�ҵ�IDΪ " << id << " ��ѧ��" << endl;
	}
}

//����ѧ����Ϣ
void saveStudentsToFile() {
	ofstream file("students.csv");

	for (int i = 0; i < num_students; i++) {
		file << students[i].id << ","
			<< students[i].name << ","
			<< students[i].password << ","
			<< students[i].role << endl;
	}

	file.close();
}


//��Ӹ�������Ϣ
void addPrincipal() {
	if (num_principal >= MAX_Users) {
		cout << "�Ѵﵽ��������������޷�����µĸ�����" << endl;
		return;
	}

	Principal newPrincipal;
	cout << "�����븺����ID��" << endl;
	cin >> newPrincipal.id;
	cout << "�����븺�������ƣ�" << endl;
	cin >> newPrincipal.name;
	cout << "�����븺�������룺" << endl;
	cin >> newPrincipal.password;
	strcpy(newPrincipal.role, "������");

	principals[num_principal] = newPrincipal;
	num_principal++;
}


//������ɾ��
void deletePrincipal() {
	char id[20];
	cout << "������Ҫɾ���ĸ�����ID��" << endl;
	cin >> id;

	ifstream inFile("principals.csv");
	ofstream outFile("temp.csv");
	string line;
	bool found = false;

	while (getline(inFile, line)) {
		stringstream ss(line);
		string tempId;
		getline(ss, tempId, ',');
		if (tempId != id) {
			outFile << line << endl;
		}
		else {
			found = true;
		}
	}

	inFile.close();
	outFile.close();

	remove("principals.csv");
	rename("temp.csv", "principals.csv");

	if (!found) {
		cout << "δ�ҵ�IDΪ " << id << " �ĸ�����" << endl;
	}
	else {
		cout << "��������Ϣɾ���ɹ�" << endl;
	}
}

//���渺������Ϣ
void savePrincipalsToFile() {
	ofstream file("principals.csv");

	for (int i = 0; i < num_principal; i++) {
		file << principals[i].id << ","
			<< principals[i].name << ","
			<< principals[i].password << ","
			<< principals[i].role << endl;
	}

	file.close();
}

//����ѧ����Ϣ
void loadStudentsFromFile() {
	ifstream file("students.csv");
	string line;
	num_students = 0; // ����ѧ������

	while (getline(file, line)) {
		stringstream ss(line);
		vector<string> fields;

		for (string field; getline(ss, field, ',');) {
			fields.push_back(field);
		}

		if (fields.size() >= 5) {  // ȷ�����㹻�������ֶ�
			strcpy(students[num_students].id, fields[0].c_str());
			strcpy(students[num_students].name, fields[1].c_str());
			strcpy(students[num_students].password, fields[4].c_str());  // ���������ǵ�����ֶ�
			num_students++;
		}
	}

	file.close();
}

//���ظ�������Ϣ
void loadPrincipalsFromFile() {
	ifstream file("principals.csv");
	string line;
	num_principal = 0; // ���ø���������

	while (getline(file, line)) {
		stringstream ss(line);
		vector<string> fields;

		for (string field; getline(ss, field, ',');) {
			fields.push_back(field);
		}

		if (fields.size() >= 5) {  // ȷ�����㹻�������ֶ�
			strcpy(principals[num_principal].id, fields[0].c_str());
			strcpy(principals[num_principal].name, fields[1].c_str());
			strcpy(principals[num_principal].password, fields[4].c_str());  // ���������ǵ�����ֶ�
			num_principal++;
		}
	}

	file.close();
}

//�����Ʒ
void addWork() {
	if (num_works >= MAX_Competitions) {
		cout << "�Ѵﵽ�����Ʒ�������޷�����µ���Ʒ" << endl;
		return;
	}

	Work newWork;
	cout << "���������ѧ��ID��" << endl;
	cin >> newWork.studentId;
	cout << "�����뾺��ID��" << endl;
	cin >> newWork.competitionId;
	cout << "��������Ʒ���ƣ�" << endl;
	cin >> newWork.workName;
	cout << "��������Ʒ������" << endl;
	cin >> newWork.workDescription;

	works[num_works] = newWork;
	num_works++;
}


//������Ʒ��Ϣ���ļ���
void saveWorksToFile() {
	ofstream file("works.csv");

	for (int i = 0; i < num_works; i++) {
		file << works[i].studentId << ","
			<< works[i].competitionId << ","
			<< works[i].workName << ","
			<< works[i].workDescription << endl;
	}

	file.close();
}

//���ļ��м�����Ʒ��Ϣ
void loadWorksFromFile() {
	ifstream file("works.csv");
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string field;
		vector<string> fields;

		while (getline(ss, field, ',')) {
			fields.push_back(field);
		}
		strcpy(works[num_works].studentId, fields[0].c_str());
		strcpy(works[num_works].competitionId, fields[1].c_str());
		strcpy(works[num_works].workName, fields[2].c_str());
		strcpy(works[num_works].workDescription, fields[3].c_str());
		num_works++;
	}
	file.close();
}

//��������
void registerForCompetition() {
	ofstream file("registrations.csv", ios::app); // ��׷��ģʽ���ļ�
	if (!file.is_open()) {
		cout << "�޷����ļ�" << endl;
		return;
	}
	char studentId[20], competitionId[20];
	cout << "����������ѧ��ID: ";
	cin >> studentId;
	cout << "�����뾺��ID: ";
	cin >> competitionId;
	// ��������Ϣд���ļ�
	file << studentId << "," << competitionId << ",δ����\n";
	file.close();
	cout << "�����ɹ���" << endl;
}



//�鿴�������
void viewResults() {
	ifstream file("results.csv");
	if (!file.is_open()) {
		cout << "�޷����ļ�" << endl;
		return;
	}

	char studentId[20];
	cout << "����������ѧ��ID�Բ鿴���: ";
	cin >> studentId;

	string line;
	bool found = false;
	while (getline(file, line)) {
		stringstream ss(line);
		string tempId, competitionId, result;
		getline(ss, tempId, ',');
		getline(ss, competitionId, ',');
		getline(ss, result, ',');

		if (tempId == studentId) {
			cout << "ѧ��ID: " << studentId << ", ����ID: " << competitionId << ", ���: " << result << endl;
			found = true;
		}
	}

	if (!found) {
		cout << "δ�ҵ�ѧ��IDΪ " << studentId << " �Ľ��" << endl;
	}

	file.close();
}

// ��������������
void enterScores() {
	ifstream inputFile("registrations.csv");
	ofstream outputFile("results.csv", ios::app); // ��׷��ģʽ���ļ�
	if (!inputFile.is_open() || !outputFile.is_open()) {
		cout << "�޷����ļ�" << endl;
		return;
	}

	string line;
	char studentId[20], competitionId[20], score[20];

	// ��ȡ������Ϣ
	while (getline(inputFile, line)) {
		stringstream ss(line);
		string tempStudentId, tempCompetitionId;
		getline(ss, tempStudentId, ',');
		getline(ss, tempCompetitionId, ',');

		cout << "Ϊѧ��ID " << tempStudentId << " �;���ID " << tempCompetitionId << " ��������: ";
		cin >> score;

		// ��������Ϣд�����ļ�
		outputFile << tempStudentId << "," << tempCompetitionId << "," << score << endl;
	}

	inputFile.close();
	outputFile.close();
	cout << "����������ɣ�" << endl;
}
//����������Ϣ
void addCompetition() {
	Competition comp;
	cout << "�����뾺��ID: ";
	cin >> comp.id;
	cout << "�����뾺������: ";
	cin >> comp.name;
	cout << "�����뾺������: ";
	cin >> comp.description;

	// д�뵽CSV�ļ�
	ofstream outFile("competitions.csv", ios::app); // ��׷��ģʽ��
	if (!outFile.is_open()) {
		cout << "�޷����ļ�" << endl;
		return;
	}

	outFile << comp.id << "," << comp.name << "," << comp.description << endl;
	outFile.close();

	cout << "������Ϣ�����ɹ���" << endl;
}

//����ѧ��������Ϣ
void manageRegistrations() {
	ifstream inFile("registrations.csv");
	if (!inFile.is_open()) {
		cout << "�޷����ļ�" << endl;
		return;
	}

	cout << "�������������" << endl;
	string line;
	while (getline(inFile, line)) {
		cout << line << endl;
	}
	inFile.close();

}



//�˺ŵ�¼
void login() {
	char account[20], password[20];
	bool isLoggedIn = false;
	int loginAttempts = 0;

	// ����Ա�˺ź�����
	char adminAccount[20] = "admin";
	char adminPassword[20] = "admin123";

	loadStudentsFromFile();  // ȷ��������ѧ����Ϣ
	loadPrincipalsFromFile();  // ȷ�������˸�������Ϣ

	while (loginAttempts < 3 && !isLoggedIn) {
		cout << "�������˺ţ�" << endl;
		cin >> account;
		cout << "���������룺" << endl;
		cin >> password;

		// ������Ա�˻�
		if (strcmp(account, adminAccount) == 0 && strcmp(password, adminPassword) == 0) {
			cout << "��¼�ɹ�����ӭ����Ա" << endl;
			adminMenu();  // ��ת������Ա�˵�
			isLoggedIn = true;
			break;
		}

		// ���ѧ���˻�
		if (!isLoggedIn) {
			for (int i = 0; i < num_students; i++) {
				if (strcmp(students[i].id, account) == 0 && strcmp(students[i].password, password) == 0) {
					cout << "��¼�ɹ�����ӭѧ�� " << students[i].name << endl;
					stdMenu();  // ��ת��ѧ���˵�
					isLoggedIn = true;
					break;
				}
			}
		}

		// ��鸺�����˻�
		if (!isLoggedIn) {
			for (int i = 0; i < num_principal; i++) {
				if (strcmp(principals[i].id, account) == 0 && strcmp(principals[i].password, password) == 0) {
					cout << "��¼�ɹ�����ӭ������ " << principals[i].name << endl;
					managerMenu();  // ��ת�������˲˵�
					isLoggedIn = true;
					break;
				}
			}
		}

		if (!isLoggedIn) {
			cout << "�˺Ż�������������³��ԡ�" << endl;
			loginAttempts++;
		}
	}

	if (!isLoggedIn) {
		cout << "�������ε�¼ʧ�ܣ������˳���" << endl;
		exit(1);
	}
}




// ����Ա�˵�����
void adminMenu() {
	int select;
	bool isAdminMenuRunning = true;

	// ����ѧ���͸�������Ϣ
	loadStudentsFromFile();
	loadPrincipalsFromFile();

	while (isAdminMenuRunning) {
		cout << "**********************" << endl;
		cout << "1. ����ѧ����Ϣ" << endl;
		cout << "2. ɾ��ѧ����Ϣ" << endl;
		cout << "3. ���Ӿ�����������Ϣ" << endl;
		cout << "4. ɾ��������������Ϣ" << endl;
		cout << "5. �鿴����ѧ����Ϣ" << endl;
		cout << "6. �鿴���и�������Ϣ" << endl;
		cout << "0. �˳�����Ա�˵�" << endl;
		cout << "**********************" << endl;
		cin >> select;
		switch (select) {
		case 1:
			addStudent();
			saveStudentsToFile();
			break;
		case 2:
			deleteStudent();
			saveStudentsToFile();
			break;
		case 3:
			addPrincipal();
			savePrincipalsToFile();
			break;
		case 4:
			deletePrincipal();
			savePrincipalsToFile();
			break;
		case 5:
			// �Ż���ʾѧ����Ϣ�ĸ�ʽ
			cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Role" << endl;
			for (int i = 0; i < num_students; i++) {
				cout << left << setw(10) << students[i].id
					<< setw(20) << students[i].name
					<< setw(10) << students[i].role << endl;
			}
			break;
		case 6:
			// �Ż���ʾ��������Ϣ�ĸ�ʽ
			cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Role" << endl;
			for (int i = 0; i < num_principal; i++) {
				cout << left << setw(10) << principals[i].id
					<< setw(20) << principals[i].name
					<< setw(10) << principals[i].role << endl;
			}
			break;
		case 0:
			isAdminMenuRunning = false;
			break;
		default:
			cout << "���벻�Ϸ�������������" << endl;
			break;
		}
	}
}

// �����˲˵�
void managerMenu() {
	int select;
	bool isRunning = true; // ����ѭ��

	while (isRunning) {
		cout << "***************" << endl;
		cout << "1. ������Ϣ����" << endl;
		cout << "2. ��������" << endl;
		cout << "3. ��Ʒ����" << endl;
		cout << "4. �˳������˵�" << endl;
		cout << "****************" << endl;
		cout << "������ѡ���ţ�";
		cin >> select;
		switch (select) {
		case 1:
			addCompetition();
			// ������Ӿ�����Ϣ����
			break;
		case 2:
			manageRegistrations();
			// ���ù�������Ϣ����
			break;
		case 3:
			enterScores();
			// ֱ�ӵ����������뺯��
			break;
		case 4:
			isRunning = false; // �˳�ѭ�����������˵�
			break;
		default:
			cout << "���벻�Ϸ�������������" << endl;
			break;
		}
	}
}



// ѧ���˵�
void stdMenu() {
	int select;
	bool isRunning = true; // ����ѭ��

	while (isRunning) {
		cout << "1. ��������" << endl;
		cout << "2. �ύ��Ʒ" << endl;
		cout << "3. �鿴���" << endl;
		cout << "4. �˳������˵�" << endl; // ����ѡ��
		cout << "������ѡ����: ";
		cin >> select;
		switch (select) {
		case 1:
			registerForCompetition();  // ֱ�ӵ��þ�����������
			break;
		case 2:
			addWork();  // ֱ�ӵ��������Ʒ����
			break;
		case 3:
			viewResults();  // ֱ�ӵ��ò鿴�������
			break;
		case 4:
			isRunning = false; // �˳�ѭ�����������˵�
			break;
		default:
			cout << "���벻�Ϸ�������������" << endl;
			break;
		}
	}
}



//������
int main()
{
	// ������ע����û�����
	loadUsersFromFile();

	int select;

	while (true)
	{
		cout << "��ѡ�������" << endl;
		cout << "1. ��¼" << endl;
		cout << "2. ע�����û�" << endl;
		cout << "0. �˳�ϵͳ" << endl;

		cin >> select;

		switch (select)
		{
		case 1:
			// ��¼����
			login();
			break;
		case 2:
			// �û�ע��
			registerUser();
			break;
		case 0:
			// �˳�ϵͳ
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
		default:
			cout << "���벻�Ϸ�������������" << endl;
			system("pause");
			system("cls"); // ����
			break;
		}
	}
	system("cls");
	system("pause");
	return 0;
}

