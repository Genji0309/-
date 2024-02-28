#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<cstring>

using namespace std;

constexpr auto MAX_Users = 100;  // 假设最大学生和负责人数量
constexpr auto MAX_Competitions = 100;  // 最大竞赛项目数量

// 定义用户结构体
typedef struct {
	char id[10];
	char username[20];
	char role[20];
	char account[20];
	char password[20];
} Users;

// 声明用户数组
Users users[MAX_Users];
int num_users = 0;

// 定义管理员结构体
typedef struct {
	char id[20];
	char name[20];
	char password[20];
	char role[20];
} Manager;

// 定义学生结构体
typedef struct {
	char id[20];
	char name[20];
	char password[20];
	char role[20];
} Student;

// 声明学生数组
Student students[MAX_Users];
int num_students = 0;

// 定义负责人结构体
typedef struct {
	char id[20];
	char name[20];
	char password[20];
	char role[20];
} Principal;

// 声明负责人数组
Principal principals[MAX_Users];
int num_principal = 0;

// 定义竞赛项目结构体
typedef struct {
	char id[20];
	char name[100];
	char description[255];
} Competition;

// 定义学生报名信息结构体
typedef struct {
	char studentId[20];
	char competitionId[20];
	char result[100];  // 存放比赛结果，例如"未评审"、"一等奖"等
} Registration;

// 定义竞赛作品结构体
typedef struct {
	char studentId[20];  // 参赛学生ID
	char competitionId[20];  // 竞赛ID
	char workName[100];  // 作品名称
	char workDescription[255];  // 作品描述
} Work;

// 声明竞赛作品数组和计数器
Work works[MAX_Competitions];

int num_works = 0;

// 函数声明
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


//函数声明
void adminMenu();
void managerMenu();
void stdMenu();


//用户注册
void registerUser() {
	if (num_users >= MAX_Users) {
		cout << "注册已满，无法注册新用户" << endl;
		return;
	}

	Users newUser;
	cout << "请输入ID：" << endl;
	cin >> newUser.id;
	cout << "请输入用户名：" << endl;
	cin >> newUser.username;
	cout << "请输入角色（负责人/学生）：" << endl;
	cin >> newUser.role;
	cout << "请输入账号：" << endl;
	cin >> newUser.account;
	cout << "请输入密码：" << endl;
	cin >> newUser.password;

	// 检查是否有重复账号
	for (int i = 0; i < num_users; i++) {
		if (strcmp(users[i].account, newUser.account) == 0) {
			cout << "该账号已被注册，请使用其他账号" << endl;
			return;
		}
	}

	users[num_users] = newUser;
	num_users++;

	// 根据角色存入不同的文件
	if (strcmp(newUser.role, "学生") == 0) {
		ofstream studentFile("students.csv", ios::app);
		studentFile << newUser.id << "," << newUser.username << "," << newUser.role << "," << newUser.account << "," << newUser.password << endl;
		studentFile.close();
	}
	else if (strcmp(newUser.role, "负责人") == 0) {
		ofstream principalFile("principals.csv", ios::app);
		principalFile << newUser.id << "," << newUser.username << "," << newUser.role << "," << newUser.account << "," << newUser.password << endl;
		principalFile.close();
	}
}



//加载用户信息
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

//添加学生信息

void addStudent() {
	if (num_students >= MAX_Users) {
		cout << "已达到最大学生数量，无法添加新的学生" << endl;
		return;
	}

	Student newStudent;
	cout << "请输入学生ID：" << endl;
	cin >> newStudent.id;
	cout << "请输入学生名称：" << endl;
	cin >> newStudent.name;
	cout << "请输入学生密码：" << endl;
	cin >> newStudent.password;
	strcpy(newStudent.role, "学生");

	students[num_students] = newStudent;
	num_students++;
}


//删除学生信息
void deleteStudent() {
	char id[20];
	cout << "请输入要删除的学生ID：" << endl;
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
		cout << "未找到ID为 " << id << " 的学生" << endl;
	}
}

//保存学生信息
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



// 从文件中加载学生信息
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

//添加负责人信息
void addPrincipal() {
	if (num_principal >= MAX_Users) {
		cout << "已达到最大负责人数量，无法添加新的负责人" << endl;
		return;
	}

	Principal newPrincipal;
	cout << "请输入负责人ID：" << endl;
	cin >> newPrincipal.id;
	cout << "请输入负责人名称：" << endl;
	cin >> newPrincipal.name;
	cout << "请输入负责人密码：" << endl;
	cin >> newPrincipal.password;
	strcpy(newPrincipal.role, "负责人");

	principals[num_principal] = newPrincipal;
	num_principal++;
}

//负责人删除
void deletePrincipal() {
	char id[20];
	cout << "请输入要删除的负责人ID：" << endl;
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
		cout << "未找到ID为 " << id << " 的负责人" << endl;
	}
	else {
		cout << "负责人信息删除成功" << endl;
	}
}

//保存负责人信息
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

// 加载负责人信息
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
//添加作品
void addWork() {
	if (num_works >= MAX_Competitions) {
		cout << "已达到最大作品数量，无法添加新的作品" << endl;
		return;
	}

	Work newWork;
	cout << "请输入参赛学生ID：" << endl;
	cin >> newWork.studentId;
	cout << "请输入竞赛ID：" << endl;
	cin >> newWork.competitionId;
	cout << "请输入作品名称：" << endl;
	cin >> newWork.workName;
	cout << "请输入作品描述：" << endl;
	cin >> newWork.workDescription;

	works[num_works] = newWork;
	num_works++;
}




//保存作品信息到文件中
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



//从文件中加载作品信息
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

//竞赛报名
void registerForCompetition() {
	ofstream file("registrations.csv", ios::app); // 以追加模式打开文件
	if (!file.is_open()) {
		cout << "无法打开文件" << endl;
		return;
	}

	char studentId[20], competitionId[20];
	cout << "请输入您的学生ID: ";
	cin >> studentId;
	cout << "请输入竞赛ID: ";
	cin >> competitionId;

	// 将报名信息写入文件
	file << studentId << "," << competitionId << ",未评审\n";
	file.close();
	cout << "报名成功！" << endl;
}

//查看比赛结果
void viewResults() {
	ifstream file("results.csv");
	if (!file.is_open()) {
		cout << "无法打开文件" << endl;
		return;
	}

	char studentId[20];
	cout << "请输入您的学生ID以查看结果: ";
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
			cout << "学生ID: " << studentId << ", 竞赛ID: " << competitionId << ", 结果: " << result << endl;
			found = true;
		}
	}

	if (!found) {
		cout << "未找到学生ID为 " << studentId << " 的结果" << endl;
	}

	file.close();
}

// 负责人评分输入
void enterScores() {
	ifstream inputFile("registrations.csv");
	ofstream outputFile("results.csv", ios::app); // 以追加模式打开文件
	if (!inputFile.is_open() || !outputFile.is_open()) {
		cout << "无法打开文件" << endl;
		return;
	}

	string line;
	char studentId[20], competitionId[20], score[20];

	// 读取报名信息
	while (getline(inputFile, line)) {
		stringstream ss(line);
		string tempStudentId, tempCompetitionId;
		getline(ss, tempStudentId, ',');
		getline(ss, tempCompetitionId, ',');

		cout << "为学生ID " << tempStudentId << " 和竞赛ID " << tempCompetitionId << " 输入评分: ";
		cin >> score;

		// 将评分信息写入结果文件
		outputFile << tempStudentId << "," << tempCompetitionId << "," << score << endl;
	}

	inputFile.close();
	outputFile.close();
	cout << "评分输入完成！" << endl;
}






//账号登陆
void login()
{
	char account[20];
	char password[20];
	int loginAttempts = 0;

	while (loginAttempts < 3) {
		cout << "请输入账号：" << endl;
		cin >> account;
		cout << "请输入密码：" << endl;
		cin >> password;

		for (int i = 0; i < num_users; i++) {
			if (strcmp(account, users[i].account) == 0 && strcmp(password, users[i].password) == 0) {
				cout << "登陆成功" << endl;
				if (strcmp(users[i].role, "管理员") == 0) {
					cout << "欢迎管理员" << users[i].username << endl;
					adminMenu();
				}
				else if (strcmp(users[i].role, "负责人") == 0) {
					cout << "欢迎负责人" << users[i].username << endl;
					managerMenu();
				}
				else if (strcmp(users[i].role, "学生") == 0) {
					cout << "欢迎学生" << users[i].username << endl;
					stdMenu();
				}
				return;
			}
		}

		cout << "账号或密码错误，请重新登录" << endl;
		loginAttempts++;
	}

	cout << "连续三次登录失败，程序将退出。" << endl;
	exit(1);
}




//管理员菜单
void adminMenu() {
	int select;
	bool isAdminMenuRunning = true;

	while (isAdminMenuRunning) {
		cout << "**********************" << endl;
		cout << "1. 增加学生信息" << endl;
		cout << "2. 删除学生信息" << endl;
		cout << "3. 增加竞赛负责人信息" << endl;
		cout << "4. 删除竞赛负责人信息" << endl;
		cout << "5. 查看所有学生信息" << endl;
		cout << "6. 查看所有负责人信息" << endl;
		cout << "0. 退出管理员菜单" << endl;
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
			cout << "输入不合法，请重新输入" << endl;
			break;
		}
	}
}

// 负责人菜单
void managerMenu() {
	int select;
	cout << "***************" << endl;
	cout << "1. 竞赛信息发布" << endl;
	cout << "2. 报名管理" << endl;
	cout << "3. 作品评审" << endl;
	cout << "4. 结果公布" << endl;
	cout << "5. 退出程序" << endl;
	cout << "****************" << endl;
	cin >> select;
	switch (select) {
	case 1:
		// 竞赛信息发布逻辑
		break;
	case 2:
		// 报名管理逻辑
		break;
	case 3:
		enterScores();  // 直接调用评分输入函数
		break;
	case 4:
		// 结果公布逻辑
		break;
	case 5:
		// 退出程序逻辑
		break;
	default:
		cout << "输入不合法，请重新输入" << endl;
		break;
	}
}


// 学生菜单
void stdMenu() {
	int select;
	cout << "1. 竞赛报名" << endl;
	cout << "2. 提交作品" << endl;
	cout << "3. 查看结果" << endl;
	cout << "请输入选项编号: ";
	cin >> select;
	switch (select) {
	case 1:
		registerForCompetition();  // 直接调用竞赛报名函数
		break;
	case 2:
		addWork();  // 直接调用添加作品函数
		break;
	case 3:
		viewResults();  // 直接调用查看结果函数
		break;
	default:
		cout << "输入不合法，请重新输入" << endl;
		break;
	}
}



//主函数
int main()
{
	// 加载已注册的用户数据
	loadUsersFromFile();

	int select;

	while (true)
	{
		cout << "请选择操作：" << endl;
		cout << "1. 登录" << endl;
		cout << "2. 注册新用户" << endl;
		cout << "0. 退出系统" << endl;

		cin >> select;

		switch (select)
		{
		case 1:
			// 登录界面
			login();
			break;
		case 2:
			// 用户注册
			registerUser();

			break;
		case 0:
			// 退出系统
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
		default:
			cout << "输入不合法，请重新输入" << endl;
			system("pause");
			system("cls"); // 清屏
			break;
		}
	}
	system("cls");
	system("pause");
	return 0;
}

