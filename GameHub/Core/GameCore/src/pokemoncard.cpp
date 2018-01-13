#include "pokemoncard.h"
#include <unordered_map>

bool PokemonCard::canPlay(Game &) const
{
  return true;
}

void energySetAmount(std::unordered_multiset<PTCG::TYPE>&_energySet, const PTCG::TYPE _energyType, const size_t remainingAmount)
{
  // Erase all of the type from the set
  _energySet.erase(_energyType);
  // Add back the remaining amount using a vector range
  std::vector<PTCG::TYPE> remaining(remainingAmount, _energyType);
  _energySet.insert(remaining.begin(), remaining.end());
}

bool PokemonCard::canAttack(Game& _game, const size_t _attackID, std::unordered_multiset<PTCG::TYPE> _attachedEnergy)
{
  // Convert the requirements to a map of type to amount required
  std::unordered_map<PTCG::TYPE, size_t> requiredEnergyAmount;
  for (const auto required : m_attacks[_attackID].requirements())
    ++requiredEnergyAmount[required];

  // Colourless energy is a wildcard, it can fill any requirement,
  // and if the requirement asks for colourless, any type will suffice.
  constexpr auto wildcard = PTCG::TYPE::COLOURLESS;
  // Get the amount of colourless requirement and remove it from the map,
  // as it needs special consideration
  size_t colourlessRequirement = requiredEnergyAmount[wildcard];
  requiredEnergyAmount.erase(wildcard);

  // Check for all typed energy, if the requirements are met
  for (const auto& energyPair : requiredEnergyAmount)
  {
    // Current type of energy we are checking
    auto& energyType = energyPair.first;
    // The amount of this type of energy we require
    auto& requiredAmount = energyPair.second;
    // Do we have the required amount of this energy type attached?
    int remainingAmount = static_cast<int>(_attachedEnergy.count(energyType)) - static_cast<int>(requiredAmount);
    if (remainingAmount >= 0)
    {
      // If so, we erase that energy from the set so we don't account for it twice
      energySetAmount(_attachedEnergy, energyType, static_cast<size_t>(remainingAmount));
    }
    // If we didn't have enough of the correct type, but we do have an equivalent,
    // amount of colourless energy, use that instead.
    else if (energyPair.second <= _attachedEnergy.count(wildcard))
    {
      // Make sure we don't use the colourless twice
      // Get the amount that will be remaining
      auto colourlessAmount = _attachedEnergy.count(wildcard) - energyPair.second;
      // Remove until we have the remaining amount
      energySetAmount(_attachedEnergy, wildcard, colourlessAmount);
    }
    // Otherwise the requirements are not met so return false
    else
      return false;
  }
  // If we have enough of any energy type to fill the colourless requirement
  return (_attachedEnergy.size() >= colourlessRequirement) && m_attacks[_attackID].canAttack(_game);
}

Card* PokemonCard::clone()
{
  return new PokemonCard(*this);
}

void PokemonCard::attack(const unsigned &_attackIndex, Game& _game)
{
  m_attacks[_attackIndex].attack(_game);
}

PTCG::CARD PokemonCard::cardType() const
{
  return PTCG::CARD::POKEMON;
}

std::string PokemonCard::preEvolution() const
{
  return m_preEvolution;
}

PTCG::TYPE PokemonCard::type() const
{
  return m_type;
}

PTCG::TYPE PokemonCard::weakness() const
{
  return m_weakness;
}

PTCG::TYPE PokemonCard::resistance() const
{
  return m_resistance;
}

int PokemonCard::hp() const
{
  return m_hp;
}

unsigned PokemonCard::retreatCost() const
{
  return m_retreatCost;
}

unsigned PokemonCard::stage() const
{
  return m_stage;
}


const std::vector<Attack>& PokemonCard::attacks() const
{
  return m_attacks;
}

unsigned PokemonCard::attackNum() const
{
  return static_cast<unsigned>(m_attacks.size());
}

