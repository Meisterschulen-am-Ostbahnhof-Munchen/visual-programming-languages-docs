# TEST_CONDITION

![TEST_CONDITION](https://github.com/user-attachments/assets/4dae2b3c-d1d5-4286-a466-46948ad2a767)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `TEST_CONDITION` dient zur Überprüfung einer Bedingung und signalisiert, ob diese erfüllt ist oder nicht. Er wird typischerweise in Testumgebungen eingesetzt, um bestimmte Bedingungen zu validieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Überprüfung der Bedingung. Wird dieser Eingang ausgelöst, beginnt der Funktionsblock mit der Auswertung des Daten-Eingangs `check`.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Überprüfung. Dieses Ereignis wird ausgelöst, nachdem die Bedingung ausgewertet wurde.

### **Daten-Eingänge**
- **check**: Ein boolescher Wert (`BOOL`), der die zu überprüfende Bedingung darstellt. 
  - Wenn `check == TRUE`, gilt die Bedingung als erfüllt (Test bestanden).
  - Wenn `check == FALSE`, gilt die Bedingung als nicht erfüllt (Test nicht bestanden).

### **Daten-Ausgänge**
- Keine vorhanden.

### **Adapter**
- Keine vorhanden.

## Funktionsweise
1. Der Funktionsblock wird durch das Ereignis `REQ` aktiviert.
2. Der Wert des Daten-Eingangs `check` wird ausgewertet.
3. Das Ergebnis der Auswertung wird intern verarbeitet (keine direkte Rückmeldung über Daten-Ausgänge).
4. Das Ereignis `CNF` wird ausgelöst, um den Abschluss der Überprüfung zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält keine komplexen Zustandsautomaten.
- Es werden keine Daten-Ausgänge bereitgestellt, da das Ergebnis der Überprüfung nur intern verarbeitet wird.

## Zustandsübersicht
Der Funktionsblock hat einen einfachen Ablauf:
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Auswertungszustand**: Wertet `check` aus und löst `CNF` aus.
3. Rückkehr zum **Idle-Zustand**.

## Anwendungsszenarien
- **Testautomatisierung**: Überprüfung von Bedingungen in automatisierten Testabläufen.
- **Fehlererkennung**: Validierung von Systemzuständen oder Eingabedaten.
- **Prototypische Implementierung**: Schnelle Integration in Testumgebungen zur Validierung von Logiken.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Testbausteinen bietet `TEST_CONDITION` eine minimalistische Schnittstelle und ist auf die Auswertung einer einzelnen Bedingung spezialisiert.
- Komplexere Testbausteine könnten zusätzliche Funktionen wie Zeitüberwachung oder mehrere Bedingungen unterstützen.

## Fazit
Der `TEST_CONDITION`-Funktionsblock ist ein einfaches, aber effektives Werkzeug zur Überprüfung von Bedingungen in Testumgebungen. Seine schlanke Schnittstelle macht ihn leicht integrierbar, während seine Funktionalität für grundlegende Validierungen ausreicht. Für komplexere Anforderungen sollten jedoch erweiterte Testbausteine in Betracht gezogen werden.
