#include "../Common/CommonFunctions.h"
#include "../Profiles/Profile.h"
#include "../SocioPath/User.h"

int main(){
   
	char result[ENC_PASS_LEN + 1], pass[PASS_LEN + 1] = "Abc123dd";
	valid_test a = checkPassValidity(pass);
	int rnd = 9;
	if (a == Valid)
		passEncrypt(pass, rnd, result);

	printf("%s", result);
}