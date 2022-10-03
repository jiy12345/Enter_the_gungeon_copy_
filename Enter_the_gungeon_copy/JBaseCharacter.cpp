#include "JBaseCharacter.h"

bool JBaseCharacter::render()
{
    JBaseObject::render();
    if (m_pGun) m_pGun->render();
    return true;
}
