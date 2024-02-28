#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<cstring>

using namespace std;

constexpr auto MAX_Users = 100;  // �������ѧ���͸���������
constexpr auto MAX_Competitions = 100;  // �������Ŀ����

// �����û��ṹ��
typedef struct {
	char id[10];
	char username[20];
	char role[20];
	char account[20];
	char password[20];
} Users;

// �����û�����
Users users[MAX_Users];
int num_users = 0;

// �������Ա�ṹ��
typedef struct {
	char id[20];
	char name[20];
	char password[20];
	char role[20];
} Manager;

// ����ѧ���ṹ��
typedef struct {
	char id[20];
	char name[20];
	char password[20];
	char role[20];
} Student;

// ����ѧ������
Student students[MAX_Users];
int num_students = 0;

// ���帺���˽ṹ��
typedef struct {
	char id[20];
	char name[20];
	char password[20];
	char role[20];
} Principal;

// ��������������
Principal principals[MAX_Users];
int num_principal = 0;

// ���徺����Ŀ�ṹ��
typedef struct {
	char id[20];
	char name[100];
	char description[255];
} Competition;

// ����ѧ��������Ϣ�ṹ��
typedef struct {
	char studentId[20];
	char competitionId[20];
	char result[100];  // ��ű������������"δ����"��"һ�Ƚ�"��
} Registration;

// ���徺����Ʒ�ṹ��
typedef struct {
	char studentId[20];  // ����ѧ��ID
	char competitionId[20];  // ����ID
	char workName[100];  // ��Ʒ����
	char workDescription[255];  // ��Ʒ����
} Work;

// ����������Ʒ����ͼ�����
Work works[MAX_Competitions];

int num_works = 0;

// ��������
void adminMenu();
void managerMenu();
void stdMenu();
void registerUser();
void loadUsersFromFile();
void addStudent();
void deleteStudent();
void saveStudentsToFile();
void loadStudentsFromFile();
void addPrincipal();
void deletePrincipal();
void savePrincipalsToFile();
void loadPrincipalsFromFile();
void login();
void addWork();
void saveWorksToFile();
void loadWorksFromFile();


//��������
void adminMenu();
void managerMenu();
void stdMenu();


//�û�ע��
void registerUser() {
	if (num_users >= MAX_Users) {
		cout << "ע���������޷�ע�����û�" << endl;
		return;
	}

	Users newUser;
	cout << "������ID��" << endl;
	cin >> newUser.id;
	cout << "�������û�����" << endl;
	cin >> newUser.username;
	cout << "�������ɫ��������/ѧ������" << endl;
	cin >> newUser.role;
	cout << "�������˺ţ�" << endl;
	cin >> newUser.account;
	cout << "���������룺" << endl;
	cin >> newUser.password;

	// ����Ƿ����ظ��˺�
	for (int i = 0; i < num_users; i++) {
		if (strcmp(users[i].account, newUser.account) == 0) {
			cout << "���˺��ѱ�ע�ᣬ��ʹ�������˺�" << endl;
			return;
		}
	}

	users[num_users] = newUser;
	num_users++;

	// ���ݽ�ɫ���벻ͬ���ļ�
	if (strcmp(newUser.role, "ѧ��") == 0) {
		ofstream studentFile("students.csv", ios::app);
		studentFile << newUser.id << "," << newUser.username << "," << newUser.role << "," << newUser.account << "," << newUser.password << endl;
		studentFile.close();
	}
	else if (strcmp(newUser.role, "������") == 0) {
		ofstream principalFile("principals.csv", ios::app);
		principalFile << newUser.id << "," << newUser.username << "," << newUser.role << "," << newUser.account << "," << newUser.password << endl;
		principalFile.close();
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



// ���ļ��м���ѧ����Ϣ
void loadStudentsFromFile() {
	ifstream file("students.csv");
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string field;
		vector<string> fields;

		while (getline(ss, field, ',')) {
			fields.push_back(field);
		}

		strcpy(students[num_students].id, fields[0].c_str());
		strcpy(students[num_students].name, fields[1].c_str());
		strcpy(students[num_students].password, fields[2].c_str());
		strcpy(students[num_students].role, fields[3].c_str());

		num_students++;
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

// ���ظ�������Ϣ
void loadPrincipalsFromFile() {
	ifstream file("principals.csv");
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string field;
		vector<string> fields;

		while (getline(ss, field, ',')) {
			fields.push_back(field);
		}

		strcpy(principals[num_principal].id, fields[0].c_str());
		strcpy(principals[num_principal].name, fields[1].c_str());
		strcpy(principals[num_principal].password, fields[2].c_str());
		strcpy(principals[num_principal].role, fields[3].c_str());

		num_principal++;
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






//�˺ŵ�½
void login()
{
	char account[20];
	char password[20];
	int loginAttempts = 0;

	while (loginAttempts < 3) {
		cout << "�������˺ţ�" << endl;
		cin >> account;
		cout << "���������룺" << endl;
		cin >> password;

		for (int i = 0; i < num_users; i++) {
			if (strcmp(account, users[i].account) == 0 && strcmp(password, users[i].password) == 0) {
				cout << "��½�ɹ�" << endl;
				if (strcmp(users[i].role, "����Ա") == 0) {
					cout << "��ӭ����Ա" << users[i].username << endl;
					adminMenu();
				}
				else if (strcmp(users[i].role, "������") == 0) {
					cout << "��ӭ������" << users[i].username << endl;
					managerMenu();
				}
				else if (strcmp(users[i].role, "ѧ��") == 0) {
					cout << "��ӭѧ��" << users[i].username << endl;
					stdMenu();
				}
				return;
			}
		}

		cout << "�˺Ż�������������µ�¼" << endl;
		loginAttempts++;
	}

	cout << "�������ε�¼ʧ�ܣ������˳���" << endl;
	exit(1);
}




//����Ա�˵�
void adminMenu() {
	int select;
	bool isAdminMenuRunning = true;

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
			for (int i = 0; i < num_students; i++) {
				cout << "ID: " << students[i].id << ", Name: " << students[i].name << ", Role: " << students[i].role << endl;
			}
			break;
		case 6:
			for (int i = 0; i < num_principal; i++) {
				cout << "ID: " << principals[i].id << ", Name: " << principals[i].name << ", Role: " << principals[i].role << endl;
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
	cout << "***************" << endl;
	cout << "1. ������Ϣ����" << endl;
	cout << "2. ��������" << endl;
	cout << "3. ��Ʒ����" << endl;
	cout << "4. �������" << endl;
	cout << "5. �˳�����" << endl;
	cout << "****************" << endl;
	cin >> select;
	switch (select) {
	case 1:
		// ������Ϣ�����߼�
		break;
	case 2:
		// ���������߼�
		break;
	case 3:
		enterScores();  // ֱ�ӵ����������뺯��
		break;
	case 4:
		// ��������߼�
		break;
	case 5:
		// �˳������߼�
		break;
	default:
		cout << "���벻�Ϸ�������������" << endl;
		break;
	}
}


// ѧ���˵�
void stdMenu() {
	int select;
	cout << "1. ��������" << endl;
	cout << "2. �ύ��Ʒ" << endl;
	cout << "3. �鿴���" << endl;
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
	default:
		cout << "���벻�Ϸ�������������" << endl;
		break;
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

