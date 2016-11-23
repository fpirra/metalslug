
#include "WeaponBonusStrategy.h"

void WeaponBonusStrategy::execute(GameObject *bonus, vector<GameObject *> &gameObjects, Player *player) {
    cout << "ejecutando agarrar arma" << bonus->getEntity() << endl;
    auto search = bulletTypes.find(bonus->getEntity());
    if (search != bulletTypes.end()) {
        applyBonus(player, search->second);
    }
    bonus->setEntity(DEAD);
}

void WeaponBonusStrategy::applyBonus(Player *player, Entity bulletType) {
    if (player->getBulletType() == bulletType) {
        int currentAmmo = player->getAmmo();
        addAmmo(player, bulletType, ammoReload);
        player->setAmmo(player->getAmmo() + currentAmmo);
    } else {
        addAmmo(player, bulletType, ammo);
    }
}

void WeaponBonusStrategy::addAmmo(Player *player, Entity &bulletType, map<Entity, int> &dictionary) {
    auto search = dictionary.find(bulletType);
    if (search != dictionary.end()) {
        player->setBulletType(bulletType);
        player->setAmmo(search->second);
    }
}
