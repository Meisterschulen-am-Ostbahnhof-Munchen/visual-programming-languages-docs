### F_NE



![F_NE](https://user-images.githubusercontent.com/116869307/214144558-e676465a-a116-46b2-87e7-fd3b912c702a.png)



<https://content.helpme-codesys.com/en/CODESYS%20Development%20System/_cds_operator_ne.html>


* * * * * * * * * *

Folgender Text wurde erzeugt von <https://chat.deepseek.com/> am 05.02.2025 und noch nicht korrekturgelesen (HF)


**Der NE-Operator in IEC 61499: Eine Einführung**

Die IEC 61499 ist eine internationale Norm, die sich mit der Modellierung von Funktionsbausteinen für industrielle Automatisierungssysteme beschäftigt. Sie bietet ein standardisiertes Framework für die Entwicklung von verteilten Steuerungssystemen, wobei logische und arithmetische Operatoren eine zentrale Rolle spielen. Einer dieser Operatoren ist der **NE-Operator** (Not Equal, „ungleich“), der in diesem Aufsatz näher beleuchtet werden soll.

### Was ist der NE-Operator?

Der NE-Operator ist ein Vergleichsoperator, der verwendet wird, um festzustellen, ob zwei Werte ungleich sind. In der IEC 61499 wird dieser Operator häufig in Funktionsbausteinen eingesetzt, um Bedingungen zu evaluieren und Entscheidungen basierend auf Vergleichen zu treffen. Der NE-Operator vergleicht zwei Eingangswerte und gibt einen booleschen Wert (`TRUE` oder `FALSE`) zurück, je nachdem, ob die Werte ungleich sind.

### Syntax und Verwendung

In der IEC 61499 wird der NE-Operator in Ausdrücken von Funktionsbausteinen verwendet. Die Syntax des NE-Operators ist wie folgt:

```
NE(Eingang1, Eingang2)
```

Hierbei sind `Eingang1` und `Eingang2` die beiden Werte, die verglichen werden sollen. Der Rückgabewert des Operators ist `TRUE`, wenn `Eingang1` ungleich `Eingang2` ist, andernfalls ist der Rückgabewert `FALSE`.

### Anwendungsbeispiele

1. **Überwachung von Sensorwerten:**
   In industriellen Prozessen ist es oft notwendig, die Werte von Sensoren zu überwachen. Der NE-Operator kann verwendet werden, um zu überprüfen, ob zwei Sensoren unterschiedliche Werte liefern:

   ```
   IF NE(Sensor1, Sensor2) THEN
       // Alarm auslösen oder Korrekturmaßnahmen einleiten
   END_IF
   ```

2. **Steuerung von Produktionsprozessen:**
   In einem Produktionsprozess kann der NE-Operator verwendet werden, um zu bestimmen, ob ein bestimmter Prozessschritt noch nicht abgeschlossen ist. Wenn der aktuelle Schritt ungleich dem Zielschritt ist, kann der Prozess fortgesetzt werden:

   ```
   IF NE(AktuellerSchritt, ZielSchritt) THEN
       // Prozess fortsetzen
   END_IF
   ```

3. **Temperaturregelung:**
   In einem Heizsystem kann der NE-Operator verwendet werden, um zu überprüfen, ob die aktuelle Temperatur ungleich der Solltemperatur ist. Wenn dies der Fall ist, kann die Heizung weiterhin aktiviert bleiben:

   ```
   IF NE(AktuelleTemperatur, SollTemperatur) THEN
       // Heizung weiter aktivieren
   END_IF
   ```

4. **Fehlererkennung:**
   Der NE-Operator kann auch zur Fehlererkennung eingesetzt werden. Wenn beispielsweise ein Sollwert und ein Istwert verglichen werden und diese nicht übereinstimmen, kann ein Fehlersignal generiert werden:

   ```
   IF NE(Sollwert, Istwert) THEN
       // Fehlersignal generieren
   END_IF
   ```

### Vorteile des NE-Operators

- **Einfache Logik:** Der NE-Operator ermöglicht es, komplexe Bedingungen in einfachen, leicht verständlichen Ausdrücken zu formulieren.
- **Flexibilität:** Der Operator kann auf verschiedene Datentypen angewendet werden, einschließlich Ganzzahlen, Gleitkommazahlen und sogar boolesche Werte.
- **Effizienz:** Durch die direkte Integration in Funktionsbausteine reduziert der NE-Operator den Bedarf an zusätzlicher Programmierung und macht den Code effizienter.
- **Robustheit:** Der NE-Operator trägt dazu bei, robuste Steuerungsalgorithmen zu entwickeln, die auf präzisen Vergleichen basieren.

### Fazit

Der NE-Operator ist ein wichtiges Werkzeug in der IEC 61499, das die Implementierung von Vergleichen in industriellen Steuerungssystemen vereinfacht. Seine Fähigkeit, festzustellen, ob zwei Werte ungleich sind, macht ihn zu einem unverzichtbaren Bestandteil in der Prozessüberwachung, Regelung und Entscheidungsfindung. Ob in der Produktionssteuerung, Temperaturregelung oder Fehlererkennung – der NE-Operator ist ein leistungsstarkes und vielseitiges Element in der Welt der industriellen Automatisierung. Durch seine Einfachheit und Effizienz trägt er dazu bei, die Entwicklung von zuverlässigen und effektiven Steuerungssystemen zu unterstützen.


















