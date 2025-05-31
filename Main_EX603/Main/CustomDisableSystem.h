
//2 Disable
//1 Enable

class KG_DisableSystem
{
public:
	KG_DisableSystem();
	/*Effect15*/
	void KG_ActivateEffect15_1();
	void KG_ActivateEffect15_2();
	/*InvisibleObjects*/
	void KG_ActivateInvisibleObjects_1();
	void KG_ActivateInvisibleObjects_2();
	~KG_DisableSystem();
	/*InvisibleArmors*/
	void KG_ActivateInvisibleArmors_1();
	void KG_ActivateInvisibleArmors_2();
	void KG_ActivateInvisibleArmors_X();
	/*InvisibleWeapons*/
	void KG_ActivateInvisibleWeapons_1();
	void KG_ActivateInvisibleWeapons_2();
	/*InvisibleWings*/
	void KG_ActivateInvisibleWings_1();
	void KG_ActivateInvisibleWings_2();
	/*InvisiblePlayer*/
	void KG_ActivateInvisiblePlayer_1();
	void KG_ActivateInvisiblePlayer_2();
	/*StaticEffect*/
	void KG_ActivateStaticEffect_1();
	void KG_ActivateStaticEffect_2();
	/*DynamicEffect*/
	void KG_ActivateDynamicEffect_1();
	void KG_ActivateDynamicEffect_2();
	/*Shades*/
	void KG_ActiveShades_1();
	void KG_ActiveShades_2();
	/*AutoCtrl*/
	void KG_AutoCtrl_1();
	void KG_AutoCtrl_2();
};extern KG_DisableSystem gCDisableSystem;