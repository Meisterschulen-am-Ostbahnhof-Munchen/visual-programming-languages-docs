# PKP_2200_LI_DI

* * * * * * * * * *
## Einleitung
Die PKP_2200_LI_DI ist eine globale Konstantendefinition für Blink Marine PowerKey Digital Inputs. Diese Konstante definiert die Pin-Zuordnungen für digitale Eingänge eines PowerKey-Systems und stellt vordefinierte Konfigurationen für verschiedene Tasten sowie einen ungültigen Zustand bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*Keine Ereignis-Eingänge vorhanden - handelt sich um eine globale Konstantendefinition*

### **Ereignis-Ausgänge**
*Keine Ereignis-Ausgänge vorhanden - handelt sich um eine globale Konstantendefinition*

### **Daten-Eingänge**
*Keine Daten-Eingänge vorhanden - handelt sich um eine globale Konstantendefinition*

### **Daten-Ausgänge**
*Keine Daten-Ausgänge vorhanden - handelt sich um eine globale Konstantendefinition*

### **Adapter**
*Keine Adapter vorhanden - handelt sich um eine globale Konstantendefinition*

## Funktionsweise
Die PKP_2200_LI_DI definiert globale Konstanten vom Typ `PKP_2200_LI_DI_S`, die die Pin-Nummern für digitale Eingänge eines Blink Marine PowerKey Systems festlegen. Jede Konstante repräsentiert eine spezifische Tastenkonfiguration mit zugeordneten Hardware-Pins.

## Technische Besonderheiten
- **Datentyp**: Alle Konstanten verwenden den Strukturtyp `PKP_2200_LI_DI_S`
- **Pin-Zuordnungen**: 
  - DigitalInput_Key_1: Pin 1
  - DigitalInput_Key_2: Pin 2
  - DigitalInput_Key_3: Pin 3
  - DigitalInput_Key_4: Pin 4
  - Invalid: Pin 255 (ungültiger Zustand)
- **Package-Zugehörigkeit**: BlinkMarine::io::DI

## Zustandsübersicht
*Keine Zustandsmaschine vorhanden - handelt sich um eine statische Konstantendefinition*

## Anwendungsszenarien
- Konfiguration von digitalen Eingängen in Marine-Steuerungssystemen
- Hardware-Abstraktion für PowerKey-Tastenbelegungen
- Vereinfachung der Pin-Zuordnung in IEC 61499-Applikationen
- Fehlerbehandlung durch definierten ungültigen Zustand

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken mit aktiver Logik handelt es sich hier um eine reine Konstantendefinition, die keine aktive Verarbeitung durchführt. Sie dient ausschließlich der zentralen Verwaltung von Hardware-Konfigurationen.

## Fazit
Die PKP_2200_LI_DI bietet eine standardisierte und wartbare Lösung für die Pin-Konfiguration digitaler Eingänge in Blink Marine PowerKey Systemen. Durch die zentrale Definition der Hardware-Zuordnungen wird die Konsistenz über verschiedene Applikationen hinweg gewährleistet und die Wiederverwendbarkeit des Codes verbessert.