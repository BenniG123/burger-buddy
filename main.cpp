#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"
#include "double_handshake_tb.h"
#include "InputWrapper.h"
#include "OrderWindow.h"
#include "DeliveryWindow.h"
#include "AdminInterface.h"
#include "Maker.h"
#include "MealCombiner.h"
#include "IngredientOrdering.h"
#include "SupplyTracker.h"
#include "MoneyManager.h"

int sc_main(int argc, char* argv[])
{
  

    // Handshake Channels
    double_handshake<Meal> OW2MC("OW2MC");
    double_handshake<Meal> MC2DW("MC2DW");
    double_handshake<int> MC2BM("MC2BM");
    double_handshake<int> MC2FM("MC2FM");
    double_handshake<int> MC2DM("MC2DM");
    sc_semaphore BM2MC("BM2MC", 0);
    sc_semaphore FM2MC("FM2MC", 0);
    sc_semaphore DM2MC("DM2MC", 0);    
    double_handshake<MoneyTransaction> MM2OW("MM2OW");
    double_handshake<MoneyTransaction> MM2IO("MM2IO");
    double_handshake<MoneyTransaction> MM2AI("MM2AI");
    double_handshake<MoneyTransaction> AI2MM("AI2MM");
    double_handshake<Meal> IW2OW("IW2OW");
    double_handshake<MoneyTransaction> IW2AI("IW2AI");
    double_handshake<MoneyTransaction> OW2MM("OW2MM");
    double_handshake<Meal> OW2ST("OW2ST");
    double_handshake<int> BM2ST("BM2ST");
    double_handshake<int> DM2ST("DM2ST");
    double_handshake<int> FM2ST("FM2ST");
    double_handshake<int> ST2BM("ST2BM");
    double_handshake<int> ST2DM("ST2DM");
    double_handshake<int> ST2FM("ST2FM");    
    double_handshake<bool> ST2OW("ST2OW");
    double_handshake<Meal> ST2IO("ST2IO");
    double_handshake<Meal> IO2ST("IO2ST");
    double_handshake<MoneyTransaction> IO2MM("IO2MM");
    
    // Input Wrapper
    InputWrapper inputWrapper("IW");
    inputWrapper.toAdminInterface(IW2AI);
    inputWrapper.toOrderWindow(IW2OW);
    
    // Order Window
    OrderWindow orderWindow("OW");
    orderWindow.fromInputWrapper(IW2OW);
    orderWindow.toMoneyManager(OW2MM);
    orderWindow.toSupplyTracker(OW2ST);
    orderWindow.toMealCombiner(OW2MC);
    orderWindow.fromMoneyManager(MM2OW);
    orderWindow.fromSupplyTracker(ST2OW); 
    
        
    
    // Admin Interface
    AdminInterface adminInterface("AI");
    adminInterface.fromInputWrapper(IW2AI);
    adminInterface.fromMoneyManager(MM2AI);
    adminInterface.toMoneyManager(AI2MM);

    // Money Manager
    MoneyManager moneyManager("MM");
    moneyManager.fromOrderWindow(OW2MM);
    moneyManager.fromIngredientOrdering(IO2MM);
    moneyManager.fromAdminInterface(AI2MM);
    moneyManager.toOrderWindow(MM2OW);
    moneyManager.toIngredientOrdering(MM2IO);
    moneyManager.toAdminInterface(MM2AI);
   
    // Supply Tracker
    SupplyTracker supplyTracker("ST");
    supplyTracker.toIngredientOrdering(ST2IO);
    supplyTracker.fromIngredientOrdering(IO2ST);
    supplyTracker.toOrderWindow(ST2OW);
    supplyTracker.fromOrderWindow(OW2ST);
    supplyTracker.fromBurgerMaker(BM2ST);
    supplyTracker.toBurgerMaker(ST2BM);
    supplyTracker.fromDrinkMaker(DM2ST);
    supplyTracker.toDrinkMaker(ST2DM);
    supplyTracker.fromFryMaker(FM2ST);
    supplyTracker.toFryMaker(ST2FM);
    
    // Ingredient Ordering
    IngredientOrdering ingredientOrdering("IO");
    ingredientOrdering.fromMoneyManager(MM2IO);
    ingredientOrdering.fromSupplyTracker(ST2IO);
    ingredientOrdering.toMoneyManager(IO2MM);
    ingredientOrdering.toSupplyTracker(IO2ST);

    // Meal Combiner
    MealCombiner MC("MC");
    MC.fromOrderWindow(OW2MC);
    MC.fromBurgerMaker(BM2MC);
    MC.fromFryMaker(FM2MC);
    MC.fromDrinkMaker(DM2MC);
    MC.toDeliveryWindow(MC2DW);
    MC.toBurgerMaker(MC2BM);
    MC.toFryMaker(MC2FM);
    MC.toDrinkMaker(MC2DM);
    
    // Makers
    Maker BM("BM");
    BM.fromMealCombiner(MC2BM);
    BM.fromSupplyTracker(ST2BM);
    BM.toMealCombiner(BM2MC);
    BM.toSupplyTracker(BM2ST);
    Maker FM("FM");
    FM.fromMealCombiner(MC2FM);
    FM.fromSupplyTracker(ST2FM);
    FM.toMealCombiner(FM2MC);
    FM.toSupplyTracker(FM2ST);
    Maker DM("DM");
    DM.fromMealCombiner(MC2DM);
    DM.fromSupplyTracker(ST2DM);
    DM.toMealCombiner(DM2MC);
    DM.toSupplyTracker(DM2ST);
    
    // Delivery Window
    DeliveryWindow deliveryWindow("DW");
    deliveryWindow.fromMealCombiner(MC2DW);

    sc_start();

    return 0;
}
