#include "../Common/CommonFunctions.h"
#include "../Profiles/Profile.h"
#include "../Profiles/ProfilesManager.h"
#include "../Profiles/ProfileUI.h"
#include "../SocioPath/ValidationUI.h"
#include "../SocioPath/Validation.h"
#include "../Common/consts.h"


int main(){
	
	bool a;

	Validation *valid = createValidation();
	deserializeValid(valid, VALIDATION_PATH);
	MainLoginDialog(valid);
}