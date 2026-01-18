# PKP_2200_LI_IX

```{index} single: PKP_2200_LI_IX
```

<img width="1893" height="365" alt="image" src="https://github.com/user-attachments/assets/4ab8ed94-c625-4318-8cef-598f76879881" />

* * * * * * * * * *

## Einleitung
Der PKP_2200_LI_IX ist ein Service-Interface-Funktionsblock für boolesche Eingangsdaten. Dieser Baustein dient als Schnittstelle für digitale Eingänge und ermöglicht die Kommunikation mit entsprechenden Hardware-Ressourcen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung mit Parametern QI, PARAMS, u8SAMember und Input
- **REQ**: Service-Anfrage mit Parameter QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit Parametern QO und STATUS
- **CNF**: Bestätigung der angeforderten Service-Operation mit Parametern QO, STATUS und IN
- **IND**: Indikation von der Ressource mit Parametern QO, STATUS und IN

### **Daten-Eingänge**
- **QI**: Event-Input-Qualifier (BOOL)
- **PARAMS**: Service-Parameter (STRING)
- **u8SAMember**: Node SA (USINT) - Standardwert: PKP_2200::PKP_2200_DEFAULT (21h)
- **Input**: Identifiziert den Eingang Input_Q1..Q8 (Typ: BlinkMarine::io::DI::PKP_2200_LI_DI_S) - Initialwert: Invalid

### **Daten-Ausgänge**
- **QO**: Event-Output-Qualifier (BOOL)
- **STATUS**: Service-Status (STRING)
- **IN**: Eingangsdaten von der Ressource (BOOL)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock initialisiert und verwaltet die Kommunikation mit digitalen Eingangsressourcen. Über den INIT-Event wird der Service mit den entsprechenden Parametern initialisiert. Der REQ-Event ermöglicht das Anfordern von Service-Operationen. Die Ausgangs-Events INITO, CNF und IND liefern Bestätigungen und Statusinformationen zurück.

## Technische Besonderheiten
- Verwendet spezifische PKP_2200-Kommunikationsparameter
- Unterstützt bis zu 8 digitale Eingänge (Q1-Q8)
- Enthält Standardwerte für SA-Member (21h = PKP_2200_DEFAULT)
- Implementiert eine Invalid-Initialisierung für Eingänge

## Zustandsübergänge
Der Baustein durchläuft folgende Zustände:
1. **Initialisierungsphase**: INIT-Event verarbeitet, INITO-Antwort generiert
2. **Service-Betrieb**: REQ-Event verarbeitet, CNF-Antwort generiert
3. **Ressourcen-Indikation**: Automatische IND-Ereignisse bei Statusänderungen

## Anwendungsszenarien
- Anbindung von digitalen Eingangssensoren in Automatisierungssystemen
- Integration in Marine-Anwendungen (BlinkMarine-Umgebung)
- Kommunikation mit PKP_2200-kompatibler Hardware
- Überwachung von Schaltzuständen und Signalpegeln

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Eingangsbausteinen bietet PKP_2200_LI_IX erweiterte Service-Funktionalitäten mit Statusrückmeldungen und Parametrisierungsmöglichkeiten. Die spezifische PKP_2200-Integration unterscheidet ihn von generischen IO-Bausteinen.

## Fazit
Der PKP_2200_LI_IX ist ein spezialisierter Service-Interface-Baustein für die zuverlässige Anbindung digitaler Eingänge in industriellen Automatisierungssystemen, insbesondere in Marine-Umgebungen. Seine erweiterte Funktionalität mit Statusrückmeldungen und Parametrisierungsoptionen macht ihn zu einer robusten Lösung für anspruchsvolle IO-Anwendungen.