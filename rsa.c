#define _CRT_SECURE_NO_WARNINGS // visual studio scanf error

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> // 処理時間はかる
#include <malloc.h>

#include<iostream> // C++

// 読みやすいため
#define and && 
#define or ||
#define NIL -1

using namespace std;

void Output(int result[]); // 出力
int Digit(int num[]); // 桁数の計算
void Trim(int num[]); // 前の0を削除
void Multiplication(int num1[], int num2[], int result[]); // 掛け算
void Addition(int num1[], int result[]); // num1 + 1
void Division(int num1[], int num2[], int result[]); // あまりの計算
void Subtraction(int num1[], int num2[], int num2_digit); // 引き算
int Comparison(int num1[], int num2[]); // 数値の比較
int DigitComparison(int num1[], int num2[], int digit); // 指定している桁数まで比較する

int main()
{
	char num1[100] = { '\0' }, num2[100] = { '\0' }, num3[100] = { '\0' }, num4[100] = { '\0' }; // 入力された数値
	int p[100], q[100], p_fi[100], q_fi[100]; // 利用できる数値
	int n[100], fi[100]; // n，φ
	int e[100]; // 秘密鍵
	int a[100], b[100];
	int testnum[100];
	int ed[100];
	int d[100];
	int m1[100], m2[100];
	int c[100];

	int i; // for
	int result[100], result2[100];
	int size; // 数値の大きさ
	int ans[100];
	int flag_p, flag_q; // 素数判定
	int p_digit, q_digit, m1_digit; // 桁数
	int difference; // 桁数の差
	int tmp; // 数値の交換
	int r[100]; // 最大公約数を求める用
	int in;

	clock_t start, start1, start2, end, end1, end2; // 処理時間測定
	double time1, time2, time;

	// 初期化
	for (i = 0; i < 100; i++) {
		p[i] = NIL;
		q[i] = NIL;
		p_fi[i] = NIL;
		q_fi[i] = NIL;
		e[i] = NIL;
		m1[i] = NIL;
	}

	start = clock(); // 始まり

	while (1) {
		cout << "3桁以上の素数を入力してください\n";
		cout << "p = ";
		cin >> num1;
		cout << "q = ";
		cin >> num2;

		// int型の配列に変更する
		i = 0;
		while (num1[i] != '\0') {
			p[i] = num1[i] - '0'; // ASCII to int array
			i++;
		}
		p[i] = NIL; // 最後尾の表示
		i = 0;
		while (num2[i] != '\0') {
			q[i] = num2[i] - '0'; // ASCII to int array
			i++;
		}
		q[i] = NIL; // 最後尾の表示

		// 桁数を計算する
		p_digit = Digit(p);
		q_digit = Digit(q);

		// 素数判定
		// p
		flag_p = 0; // 初期化
		// for文で回す数値の初期化
		testnum[0] = 2;
		for (i = 1; i < 100; i++) {
			testnum[i] = NIL;;
		}
		while (1) {
			Division(p, testnum, result); // あまりを取る

			if (result[0] == 0 and result[1] == NIL) { // あまりを0だったら素数でない
				flag_p = 1;
				break;
			}

			// testnum + 1
			Addition(testnum, ans);
			i = 0;
			while (ans[i] != NIL) {
				testnum[i] = ans[i];
				i++;
			}
			testnum[i + 1] = NIL;

			size = Comparison(p, testnum);
			if (size == 2) { // i < pまで実行する
				break;
			}
		}
		// q
		flag_q = 0; // 初期化
		// for文で回す数値の初期化
		testnum[0] = 2;
		for (i = 1; i < 100; i++) {
			testnum[i] = NIL;;
		}
		while (1) {
			Division(q, testnum, result);

			if (result[0] == 0 and result[1] == NIL) {
				flag_q = 1;
				break;
			}

			// testnum + 1
			Addition(testnum, ans);
			i = 0;
			while (ans[i] != NIL) {
				testnum[i] = ans[i];
				i++;
			}
			testnum[i] = NIL;

			size = Comparison(q, testnum);
			if (size == 2) { // i < pまで実行する
				break;
			}
		}

		if (flag_p == 1) {
			Output(p);
			cout << "は素数でない．\n";
		}
		if (flag_q == 1) {
			Output(q);
			cout << "は素数でない．\n";
		}

		if (p_digit >= 3 and q_digit >= 3 and flag_p == 0 and flag_q == 0) { // 条件をすべて満たしたらwhile文から抜ける
			break;
		}
	}

	// p-1 と q-1 を求める
	i = 0;
	while (1) {
		if (p[i] == NIL) {
			p_fi[i - 1] -= 1;
			break;
		}
		else {
			p_fi[i] = p[i];
		}
		i++;
	}
	i = 0;
	while (1) {
		if (q[i] == NIL) {
			q_fi[i - 1] -= 1;
			break;
		}
		else {
			q_fi[i] = q[i];
		}
		i++;
	}

	cout << "\n---------------------- RSA -------------------------\n";
	cout << "p = " << num1 << "，q = " << num2 << "\n";

	Multiplication(p, q, n); // n = p * q

	cout << "n = ";
	Output(n);

	Multiplication(p_fi, q_fi, fi); // φ = (p -1) * (q - 1)

	cout << "，φ = ";
	Output(fi);
	cout << "\n";

	// 秘密鍵を入力する
	while (1) {
		Output(fi);
		cout << "と素の整数e(1<e<";
		Output(n);
		cout << ")を入力してください：";
		cin >> num3;

		// int型の配列に変更する
		i = 0;
		while (num3[i] != '\0') {
			e[i] = num3[i] - '0'; // ASCII to int array
			i++;
		}

		// 最大公約数を求める
		// 一時的に保存する
		i = 0;
		while (1) {
			a[i] = fi[i];
			if (fi[i] == NIL) {
				break;
			}
			i++;
		}
		a[i] = NIL;
		i = 0;
		while (1) {
			b[i] = e[i];
			if (e[i] == NIL) {
				break;
			}
			i++;
		}
		b[i] = NIL;

		size = Comparison(a, b);
		if (size == 0) { // a < b の時aとbを交換する
			difference = Digit(b) - Digit(a);
			for (i = Digit(a); i >= 0; i--) {
				a[i + 1] = a[i];
			}
			for (i = 0; i < difference; i++) {
				a[i] = 0;
			}
			for (i = 0; i < Digit(b); i++) {
				tmp = a[i];
				a[i] = b[i];
				b[i] = tmp;
			}

			Trim(a); // 前の0を削除
		}

		Division(a, b, r); // あまりを取る

		// 最初に0が得られた場合while文に入る必要はない
		in = 0;
		if (r[0] == 0 and r[1] == NIL) {
			in = 1;
		}
		while (in == 0) {
			for (i = 0; i < Digit(b); i++) {
				a[i] = b[i];
			}
			a[i] = NIL;
			Trim(a);

			for (i = 0; i < Digit(r); i++) {
				b[i] = r[i];
			}
			b[i] = NIL;
			Trim(b);

			Division(a, b, r);

			if (r[0] == 0 and r[1] == NIL) { // あまりが0の時while文から抜ける
				break;
			}
		}

		// 最大公約数が1の時互いに素である
		if (b[0] == 1 and b[1] == NIL) {
			break;
		}
		else {
			Output(e);
			cout << "と";
			Output(fi);
			cout << "の最大公約数は";
			Output(b);
			cout << "となるため，互いに素でない．\n";
		}
	}

	cout << "e = ";
	Output(e);
	cout << "\n";

	/****** 暗号化 ******/

	/****** ↓時間測定1↓ ******/
	start1 = clock(); // 開始時間

	// d初期化
	d[0] = 0;
	for (i = 1; i < 100; i++) {
		d[i] = NIL;;
	}
	while (1) { // e*d mod fi = 1 を満たすdを探す
		// d++
		Addition(d, ans);
		i = 0;
		while (ans[i] != NIL) {
			d[i] = ans[i];
			i++;
		}
		d[i] = NIL;

		Multiplication(e, d, ed); // ed = e * d

		// (e * d) mod φ = 1 を満たすdを探す
		Division(ed, fi, result);
		if (result[0] == 1 and result[1] == NIL) { // 条件満たしたらwhile分から抜ける
			break;
		}
	}
	cout << "d = ";
	Output(d);
	cout << "\n";

	end1 = clock(); // 終了時間
	/****** ↑時間測定1↑ ******/

	time1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
	cout << "処理時間：" << time1 << "[s]\n\n";

	// 平文の入力
	while (1) {
		cout << "2桁の数値を入力してください:";
		cin >> num4;

		// int型の配列に変更する
		i = 0;
		while (num4[i] != '\0') {
			m1[i] = num4[i] - '0'; // ASCII to int array
			i++;
		}
		m1[i] = NIL; // 最後尾の表示

		m1_digit = Digit(m1);

		if (m1_digit == 2 or m1_digit == 1) { // 2桁を満たすまで繰り返す
			break;
		}
	}

	/********** c = m^e mod n **********/
	Division(m1, n, result); // m1 mod n
	// 得られた結果がcに代入する
	i = 0;
	while (result[i] != NIL) {
		c[i] = result[i];
		i++;
	}
	c[i] = NIL; // 最後尾の表示

	// 初期化
	testnum[0] = 1;
	for (i = 1; i < 100; i++) {
		testnum[i] = NIL;
	}
	while (1) { // だんだん数値をかけて，そのあまりを取る
		// c = (c * m1) % n;
		Multiplication(c, m1, result);
		Division(result, n, result2);

		i = 0;
		while (result2[i] != NIL) {
			c[i] = result2[i];
			i++;
		}
		c[i] = NIL;

		// testnum + 1
		Addition(testnum, ans);
		i = 0;
		while (ans[i] != NIL) {
			testnum[i] = ans[i];
			i++;
		}
		testnum[i] = NIL;

		size = Comparison(testnum, e);

		if (size == 2) { // e回を計算したら終了する
			break;
		}
	}

	cout << "c = ";
	Output(c);
	cout << "\n";

	/********* 復号 (c^d mod n = m2) *********/

	/****** ↓時間測定2↓ ******/
	start2 = clock(); // 開始時間

	Division(c, n, result);
	// 得られた結果がm2に代入する
	i = 0;
	while (result[i] != NIL) {
		m2[i] = result[i];
		i++;
	}
	m2[i] = NIL; // 最後尾を表示する

	// 初期化
	testnum[0] = 1;
	for (i = 1; i < 100; i++) {
		testnum[i] = NIL;
	}
	while (1) {
		// m2 = (m2 * c) % n;
		Multiplication(m2, c, result);
		Division(result, n, result2);

		i = 0;
		while (result2[i] != NIL) {
			m2[i] = result2[i];
			i++;
		}
		m2[i] = NIL;

		// testnum + 1
		Addition(testnum, ans);
		i = 0;
		while (ans[i] != NIL) {
			testnum[i] = ans[i];
			i++;
		}
		testnum[i] = NIL;

		size = Comparison(testnum, d);

		if (size == 2) { // e回を計算したら終了する
			break;
		}
	}

	cout << "m = ";
	Output(m2);
	cout << "\n";

	end2 = clock(); // 終了時間
	end = clock();
	/****** ↑時間測定2↑ ******/

	time2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
	cout << "処理時間：" << time2 << "[s]\n\n";

	size = Comparison(m1, m2);
	if (size == 2) {
		cout << "復号成功した！\n";
	}
	else {
		cout << "復号失敗した......\n";
	}

	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "全体処理時間：" << time << "[s]\n\n";

	system("pause"); // 続行するには何かキーを押してください . . .

	return 0;
}

// 出力
void Output(int result[])
{
	int i, j;

	if (result[0] == 0 and result[1] == NIL) { // 結果が0の場合
		cout << "0";
	}
	else {
		// 前の0を計算して，
		i = 0;
		while (1) {
			if (result[i] == 0) {
				i += 1;
			}
			else {
				j = i;
				break;
			}
		}
		// 0でない桁から出力する
		i = j;
		while (1) {
			if (result[i] == NIL) {
				break;
			}
			cout << result[i];
			i++;
		}
	}
}

// 桁数の計算
int Digit(int num[])
{
	int digit = 0;

	while (1) {
		if (num[digit] != NIL) {
			digit += 1;
		}
		else if (num[digit] == NIL) {
			break;
		}
	}

	return digit;
}

// 前の0を削除
void Trim(int num[])
{
	int i = 0, j;

	while (1) {
		if (num[i] == 0) {
			i += 1;
		}
		else {
			j = i;
			break;
		}
	}
	for (i = j; i < 100; i++) {
		num[i - j] = num[i];
		if (num[i] == NIL) {
			break;
		}
	}
}

// 掛け算
void Multiplication(int num1[], int num2[], int result[])
{
	int num1_digit, num2_digit; // 掛け算する数値の桁数
	int i, j;  // for
	int carry, temp; // 桁上げの保存，値を一時的に保存

	// 桁数を計算する
	num1_digit = Digit(num1);
	num2_digit = Digit(num2);

	// 初期化
	for (i = 0; i < num1_digit + num2_digit; i++) {
		result[i] = 0;
	}
	result[num1_digit + num2_digit] = NIL; // 最後尾を表示

	for (i = num2_digit - 1; i >= 0; i--) {
		carry = 0; // 桁上げ初期化
		for (j = num1_digit - 1; j >= 0; j--) {
			temp = num2[i] * num1[j] + carry; // 掛け算して，桁上げを足す

			carry = temp / 10; // 桁上げの計算
			temp = temp % 10;

			result[i + j + 1] += temp; // 値を代入
			carry = carry + result[i + j + 1] / 10; // 新たに桁上げを計算する
			result[i + j + 1] = result[i + j + 1] % 10;
		}
		// 最後の1桁が桁上げがあるかどうかを判断する
		if (carry > 0) {
			result[i + j + 1] = carry;
		}
	}

	Trim(result); // 前の0を削除う
}

// num1 + 1
void Addition(int num1[], int result[])
{
	int num1_digit; // 足し算する数値の桁数
	int i;  // for
	int carry, keep; // 桁上げの保存，値を一時的に保存

	num1_digit = Digit(num1); // 桁数を計算する

	// 初期化
	for (i = 0; i < num1_digit; i++) {
		result[i] = 0;
	}
	result[num1_digit] = NIL; // 最後尾を表示する
	carry = 0;
	for (i = num1_digit - 1; i >= 0; i--) {
		if (i == num1_digit - 1) { // 1桁目 + 1
			keep = num1[i] + 1;

			carry = keep / 10; // 桁上げの計算
			keep = keep % 10;

			result[i] += keep;
			carry = carry + result[i] / 10;
			result[i] = result[i] % 10;
		}
		else {
			keep = num1[i] + carry;

			carry = keep / 10;
			keep = keep % 10;

			result[i] += keep;
			carry = carry + result[i] / 10;
			result[i] = result[i] % 10;
		}
	}

	// 最後に桁上げあるかどうかを判断する
	if (carry > 0) {
		for (i = num1_digit; i >= 0; i--) {
			result[i + 1] = result[i];
		}
		result[0] += carry;
	}
}

// あまりの計算
void Division(int num1[], int num2[], int result[])
{
	int num1_keep[100], num2_keep[100];
	int num1_digit, num2_digit; // 掛け算する数値の桁数
	int i;  // for
	int size;
	int zero;

	// 他の変数に一時的に保存し，桁数を計算する
	num1_digit = 0;
	while (1) {
		if (num1[num1_digit] != NIL) {
			num1_keep[num1_digit] = num1[num1_digit];
			num1_digit += 1;
		}
		else if (num1[num1_digit] == NIL) {
			num1_keep[num1_digit] = NIL;
			break;
		}
	}
	num2_digit = 0;
	while (1) {
		if (num2[num2_digit] != NIL) {
			num2_keep[num2_digit] = num2[num2_digit];
			num2_digit += 1;
		}
		else if (num2[num2_digit] == NIL) {
			num2_keep[num2_digit] = NIL;
			break;
		}
	}

	// 初期化
	for (i = 0; i < num1_digit; i++) {
		result[i] = 0;
	}
	result[num1_digit] = NIL; // 最後尾を表示

	size = Comparison(num1_keep, num2_keep);
	//cout << "size = " << size << "\n";

	if (size == 0) { // num1_keep < num2_keep
		for (i = 0; i < num1_digit; i++) {
			result[i] = num1_keep[i];
		}
		result[num1_digit] = NIL; // 最後尾を表示
	}
	else {
		while (1) {
			size = DigitComparison(num1_keep, num2_keep, num2_digit); // 大きさの判断

			if (size == 0) { // 小さかったら，num2が後ろ1桁をずらす
				for (i = num2_digit; i >= 0; i--) {
					num2_keep[i + 1] = num2_keep[i];
				}
				num2_keep[0] = 0; // 先頭に0を加える
				num2_digit += 1; // 桁数を更新する
				size = DigitComparison(num1_keep, num2_keep, num2_digit); // もう一度大きさを判別する
			}

			while (size != 0) { // あまりがnum2より小さいまで実行する
				Subtraction(num1_keep, num2_keep, num2_digit); // 引き算
				size = DigitComparison(num1_keep, num2_keep, num2_digit); // 使った数値の大きさの判定
			}



			if (num1_digit == num2_digit) { // 桁数が同じだったらwhile文から抜ける
				break;
			}
		}
	}

	if (size != 2) {
		for (i = 0; i <= num2_digit; i++) {
			result[i] = num1_keep[i];
		}
	}

	// あまりが0かどうかの判断
	i = 0;
	zero = 1;
	while (1) {
		if (result[i] == 0) {
		}
		else if (result[i] == NIL) {
			zero = 0;
			break;
		}
		else {
			break;
		}
		i++;
	}

	if (zero == 0) {
		result[0] = 0;
		result[1] = NIL;
	}
	else {
		Trim(result); // 前の0を削除
	}
}

// 引き算
void Subtraction(int num1[], int num2[], int num2_digit)
{
	int i;

	for (i = num2_digit - 1; i >= 0; i--) { // それぞれ対応する数値を引き算する
		num1[i] = num1[i] - num2[i];
	}

	for (i = num2_digit - 1; i >= 0; i--) { // 値が負の場合前の1桁に借りる
		if (num1[i] < 0) {
			num1[i] += 10;
			num1[i - 1] -= 1;
		}
	}
}

// 数値の比較
int Comparison(int num1[], int num2[])
{
	int num1_digit, num2_digit; // 掛け算する数値の桁数
	int size = NIL;
	int i;

	// 桁数を計算する
	num1_digit = Digit(num1);
	num2_digit = Digit(num2);

	//cout << "digit num1 = " << num1_digit << " , digit num2 = " << num2_digit << "\n";

	if (num1_digit < num2_digit) {
		size = 0; // num1 < num2
	}
	else if (num1_digit > num2_digit) {
		size = 1; // num1 > num2
	}
	else if (num1_digit == num2_digit) {
		for (i = 0; i < num1_digit; i++) {
			if (num1[i] < num2[i]) {
				size = 0; // num1 < num2
				break;
			}
			else if (num1[i] > num2[i]) {
				size = 1; // num1 > num2
				break;
			}
		}
		if (size == NIL) {
			size = 2; // num1 = num2
		}
	}

	return size;
}

// 指定している桁数まで比較する
int DigitComparison(int num1[], int num2[], int digit)
{
	int i, size;

	for (i = 0; i < digit; i++) { // 最初から入った数値を比較する
		if (num1[i] < num2[i]) {
			size = 0; // num1 < num2
			break;
		}
		else if (num1[i] > num2[i]) {
			size = 1; // num1 > num2
			break;
		}
	}
	if (i == digit) {
		size = 1; // num1 >= num2
	}

	return size;
}
