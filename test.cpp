#include <string>
#include <vector>

class Greeter;
class Recipe;
class RecipeDatabase;
class PlanManager;
class Date;
class Meal;

class IIKH_system { 
public:
	IIKH_system(); // IIKH_system 생성자

private:
	Greeter* greeter; // greeter 객체

	void showGreeter(Greeter* greeter); // greeter 표시
	void startProgram(); // 프로그램 실행
	void quitProgram(); // 프로그램 종료
};

class Greeter {
public:
	Greeter(); // greeter 생성자
	RecipeDatabase* db; // 레시피DB 객체
	PlanManager* planmanager; // 플랜매니저 객체
	void showRecipeDatabase(); // 레시피DB 표시
	void showPlanManager(); // 플랜매니저 표시

private:
	std::string imagePath; // 이미지가 저장된 위치
	std::string greetingText; // 표시할 텍스트

	void createRecipeDatabase(); // 레시피DB 객체 생성
	char keypressListener(); // 키입력 리스너, greeter 종료 시점 파악
	void printGreeting(); // 인사 표시
	void showImage(std::string imagePath); // 이미지 표시
};

class RecipeDatabase {
public:
	RecipeDatabase(); // 레시피DB 생성자
	void addRecipe(Recipe* recipe); // 레시피 추가
	void removeRecipe(Recipe* recipe); // 레시피 삭제
	void showRecipes(); // 레시피 표시

private:
	std::vector<Recipe*> recipeList; // 레시피 목록
	std::string recipeDatabasePath; // 레시피DB 파일이 저장된 위치

	void loadRecipesFromDatabaseFile(std::string filePath); // 레시피DB 파일에서 레시피 목록 불러오기
	int recipeClickListener(); // 레시피 클릭 리스너, 어느 레시피가 선택되었는지 파악
	std::vector<Recipe*> searchIngredients(std::vector<std::string> ingredients); // 레시피 재료 검색, 검색 시 salmon이나 dill-weed 등의 재료 기준으로 검색하기 때문에 이름이 아닌 재료로 검색함.
	std::string determineCategory(Recipe recipe); // 레시피의 카테고리를 결정
	void assignCategory(); // 레시피의 카테고리를 부여
	std::string requestName(); // 레시피 이름 입력을 요청
};

class Recipe {
public:
	Recipe(std::string name, std::vector<std::string> preparationSteps, int expectedPreparationTime, std::string imagePath, int recipeId);
    // 레시피 생성자
	bool isIngredientIncluded(std::string ingredient); // 재료 포함 여부 확인, RecipeDatebase.searchIngredients()의 구현에서 활용
	void editIngredients(std::vector<std::string> newIngredients); // 재료 수정
	void editSteps(std::vector<std::string> newSteps); // 조리법 수정
	void showImage(std::string imagePath); // 이미지 표시
	void showRecipe(); // 레시피 표시
	void exitWindow(); // 레시피 창 종료

private:
	int recipeId; // 레시피 ID
	std::string name; // 레시피 이름
	std::vector<std::string> ingredients; // 레시피 재료
	std::vector<std::string> preparationSteps; // 레시피 조리법
	int expectedPreparationTime; // 레시피 예상 조리 시간
	std::string imagePath; // 레시피 이미지가 저장된 위치
	std::string category; // 레시피 카테고리
};

class PlanManager {
public:
	PlanManager(); // 플랜매니저 생성자
	void createPlan(); // 플랜 생성
	void editPlan(Date* date); // 플랜 수정
	void printRecipes(); // 레시피 표시

private:
	std::vector<Date*> dates; // 날짜(플랜) 목록
};

class Date {
public:
	Date(); // 날짜 생성자
	void printAnnotations(); // 날짜에 대한 사용자의 메모 표시
	void printAllInfo(); // 날짜에 대한 모든 정보 표시

private:
	int year; // 연도
	int month; // 월
	int day; // 일
	std::vector<std::string> annotations; // 사용자의 메모
	std::vector<Meal*> meals; // 끼니 목록
};

class Meal {
public:
	Meal(); // 끼니 생성자
	void printMeal(); // 끼니에 대한 정보 표시
    
private:
	std::vector<Recipe*> recipes; // 레시피 목록
	RecipeDatabase* db; // 레시피DB 객체, 이를 통해 개별 레시피 접근
};