import numpy as np
import skfuzzy as fuzz
import skfuzzy.control as ctrl
import matplotlib.pyplot as plt

precipitation = ctrl.Antecedent(np.arange(0, 101, 1), "Уровень осадков")
temperature = ctrl.Antecedent(np.arange(-10, 26, 1), "Среднесуточная температура")
melting_rate = ctrl.Consequent(np.arange(0, 61, 1), "Скорость таяния")

precipitation['Низкий'] = fuzz.gaussmf(precipitation.universe, 0, 30)
precipitation['Средний'] = fuzz.gaussmf(precipitation.universe, 50, 15)
precipitation['Высокий'] = fuzz.gaussmf(precipitation.universe, 100, 30)

temperature['Низкая'] = fuzz.gaussmf(temperature.universe, -10, 10)
temperature['Средняя'] = fuzz.gaussmf(temperature.universe, 7.5, 5)
temperature['Высокая'] = fuzz.gaussmf(temperature.universe, 25, 10)

melting_rate['Низкая'] = fuzz.trimf(melting_rate.universe, [0, 0, 25])
melting_rate['Средняя'] = fuzz.trimf(melting_rate.universe, [20, 30, 40])
melting_rate['Высокая'] = fuzz.trimf(melting_rate.universe, [35, 60, 60])

# precipitation.view()
# temperature.view()
# melting_rate.view()

rule1 = ctrl.Rule(antecedent=precipitation['Низкий'] & temperature['Низкая'], consequent=melting_rate['Низкая'])
rule2 = ctrl.Rule(antecedent=precipitation['Низкий'] & temperature['Средняя'], consequent=melting_rate['Низкая'])
rule3 = ctrl.Rule(antecedent=precipitation['Низкий'] & temperature['Высокая'], consequent=melting_rate['Средняя'])

rule4 = ctrl.Rule(antecedent=precipitation['Средний'] & temperature['Низкая'], consequent=melting_rate['Низкая'])
rule5 = ctrl.Rule(antecedent=precipitation['Средний'] & temperature['Средняя'], consequent=melting_rate['Средняя'])
rule6 = ctrl.Rule(antecedent=precipitation['Средний'] & temperature['Высокая'], consequent=melting_rate['Высокая'])

rule7 = ctrl.Rule(antecedent=precipitation['Высокий'] & temperature['Низкая'], consequent=melting_rate['Средняя'])
rule8 = ctrl.Rule(antecedent=precipitation['Высокий'] & temperature['Средняя'], consequent=melting_rate['Высокая'])
rule9 = ctrl.Rule(antecedent=precipitation['Высокий'] & temperature['Высокая'], consequent=melting_rate['Высокая'])

prob_ctrl = ctrl.ControlSystem(rules = [rule1, rule2, rule3, rule4, rule5, rule6, rule7, rule8, rule9])
probbing = ctrl.ControlSystemSimulation(prob_ctrl)


probbing.input["Уровень осадков"] = 10
probbing.input["Среднесуточная температура"] = 10

probbing.compute()
print(probbing.output["Скорость таяния"])

precipitation.view(sim=probbing)
temperature.view(sim=probbing)
melting_rate.view(sim=probbing)

plt.tight_layout()
plt.show()
