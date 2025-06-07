# sequence_E_04

![sequence_E_04](https://github.com/user-attachments/assets/b04f44cb-8db8-4ad9-807e-b724659dd20c)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `sequence_E_04` ist eine Zustandsmaschine, die eine sequenzielle Abfolge von vier Zuständen steuert.
Jeder Zustand aktiviert eine spezifische Ausgabe, und die Übergänge zwischen den Zuständen werden durch Ereignisse ausgelöst.
Der Baustein eignet sich ideal für Anwendungen, die eine schrittweise Abarbeitung von Prozessen erfordern, wie z. B. Steuerungsabläufe in der Automatisierungstechnik.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `START_S1`: Wechsel vom Startzustand (`xSTART`) zu `State_01`.
- `S1_S2`: Wechsel von `State_01` zu `State_02`.
- `S2_S3`: Wechsel von `State_02` zu `State_03`.
- `S3_S4`: Wechsel von `State_03` zu `State_04`.
- `S4_START`: Wechsel von `State_04` zurück zum Startzustand (`sState_00`).
- `RESET`: Setzt die Zustandsmaschine von jedem Zustand zurück zum Startzustand (`sState_00`).

### **Ereignis-Ausgänge**

- `CNF`: Bestätigt die Ausführung eines Zustandswechsels und liefert die aktuelle Zustandsnummer (`STATE_NR`).
- `EO_S1`: Wird bei Aktivierung von `State_01` ausgelöst und liefert den Wert von `DO_S1`.
- `EO_S2`: Wird bei Aktivierung von `State_02` ausgelöst und liefert den Wert von `DO_S2`.
- `EO_S3`: Wird bei Aktivierung von `State_03` ausgelöst und liefert den Wert von `DO_S3`.
- `EO_S4`: Wird bei Aktivierung von `State_04` ausgelöst und liefert den Wert von `DO_S4`.

### **Daten-Eingänge**

- Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

- `STATE_NR` (SINT): Gibt die aktuelle Zustandsnummer aus (0 für Startzustand, 1 für `State_01`, usw.).
- `DO_S1` (BOOL): Aktiviert die Ausgabe für `State_01`.
- `DO_S2` (BOOL): Aktiviert die Ausgabe für `State_02`.
- `DO_S3` (BOOL): Aktiviert die Ausgabe für `State_03`.
- `DO_S4` (BOOL): Aktiviert die Ausgabe für `State_04`.

### **Adapter**

- Keine Adapter vorhanden.

## Funktionsweise

Der Baustein durchläuft eine festgelegte Sequenz von Zuständen, beginnend mit `xSTART`.
Jeder Zustand aktiviert eine spezifische Ausgabe (`DO_S1` bis `DO_S4`), und die Übergänge zwischen den Zuständen werden durch die entsprechenden Ereignisse (`START_S1`, `S1_S2`, usw.) ausgelöst.
Der `RESET`-Eingang ermöglicht es, die Sequenz jederzeit zurückzusetzen.
Bei jedem Zustandswechsel wird das `CNF`-Ereignis ausgelöst, um die aktuelle Zustandsnummer zu bestätigen.

## Technische Besonderheiten

- **Zustandsverwaltung**: Die Zustandsmaschine verwendet einen klaren Aufbau mit Eintritts- (`_E`), Austritts- (`_X`) und Bestätigungsalgorithmen (`_C`), um die Ausgaben und Zustandsnummern zu aktualisieren.
- **Reset-Funktion**: Der `RESET`-Eingang deaktiviert alle Ausgaben und bringt die Maschine zurück in den Startzustand.
- **Ereignisgesteuerte Übergänge**: Die Sequenz wird ausschließlich durch Ereignisse gesteuert, was eine präzise Steuerung ermöglicht.

## Zustandsübersicht

1. **xSTART**: Initialzustand, keine aktiven Ausgaben.
2. **sState_01**: Aktiviert `DO_S1`.
3. **sState_02**: Deaktiviert `DO_S1` und aktiviert `DO_S2`.
4. **sState_03**: Deaktiviert `DO_S2` und aktiviert `DO_S3`.
5. **sState_04**: Deaktiviert `DO_S3` und aktiviert `DO_S4`.
6. **sState_00**: Deaktiviert `DO_S4` und kehrt zum Startzustand zurück.
7. **sRESET**: Zwischenzustand für den Reset, deaktiviert alle Ausgaben.

## Anwendungsszenarien

- **Industrielle Automatisierung**: Steuerung von Maschinenabläufen mit sequenziellen Schritten.
- **Prozesssteuerung**: Abarbeitung von Prozessschritten in einer festgelegten Reihenfolge.
- **Testautomation**: Automatisierte Testsequenzen mit Zustandsüberwachung.

## Vergleich mit ähnlichen Bausteinen

- **Vorteile**: Klare Ereignissteuerung, einfache Reset-Funktion, gut dokumentierte Zustandsübergänge.
- **Nachteile**: Keine Daten-Eingänge für dynamische Anpassungen, feste Anzahl von Zuständen (4).

## Fazit

Der `sequence_E_04`-Baustein ist eine robuste Lösung für Anwendungen, die eine ereignisgesteuerte Sequenzabarbeitung erfordern.
Seine klare Struktur und die einfache Reset-Funktion machen ihn besonders geeignet für industrielle Steuerungsaufgaben.
Für komplexere Anwendungen mit variabler Zustandsanzahl oder dynamischen Eingaben könnten jedoch Erweiterungen erforderlich sein.
