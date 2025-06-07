# sequence_E_04_loop  

![sequence_E_04_loop](https://github.com/user-attachments/assets/6999fbd6-155d-4aa2-a8c5-b5a0d393c3bf)

* * * * * * * * * *  

## Einleitung  

Der Funktionsbaustein **sequence_E_04_loop** ist eine zyklische Zustandsmaschine, die eine sequenzielle Abfolge von vier Zuständen steuert und nach dem letzten Zustand automatisch zum ersten Zustand zurückkehrt.
Im Gegensatz zum nicht-zyklischen Pendant **sequence_E_04** ermöglicht dieser Baustein eine endlose Wiederholung der Sequenz, was ihn ideal für Anwendungen mit periodischen Prozessen macht, z. B. in Produktionslinien oder Testautomation.  

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  

- **START_S1**: Wechsel vom Startzustand (**xSTART**) zu **State_01**.  
- **S1_S2**: Wechsel von **State_01** zu **State_02**.  
- **S2_S3**: Wechsel von **State_02** zu **State_03**.  
- **S3_S4**: Wechsel von **State_03** zu **State_04**.  
- **S4_S1**: Wechsel von **State_04** zurück zu **State_01** (zyklischer Übergang).  
- **RESET**: Setzt die Zustandsmaschine von jedem Zustand zurück zum Startzustand (**xSTART**).  

### **Ereignis-Ausgänge**  

- **CNF**: Bestätigt die Ausführung eines Zustandswechsels und liefert die aktuelle Zustandsnummer (**STATE_NR**).  
- **EO_S1**: Wird bei Aktivierung von **State_01** ausgelöst und liefert den Wert von **DO_S1**.  
- **EO_S2**: Wird bei Aktivierung von **State_02** ausgelöst und liefert den Wert von **DO_S2**.  
- **EO_S3**: Wird bei Aktivierung von **State_03** ausgelöst und liefert den Wert von **DO_S3**.  
- **EO_S4**: Wird bei Aktivierung von **State_04** ausgelöst und liefert den Wert von **DO_S4**.  

### **Daten-Eingänge**  

- Keine Daten-Eingänge vorhanden.  

### **Daten-Ausgänge**  

- **STATE_NR** (SINT): Gibt die aktuelle Zustandsnummer aus (0 für Startzustand, 1 für **State_01**, 2 für **State_02**, usw.).  
- **DO_S1** (BOOL): Aktiviert die Ausgabe für **State_01**.  
- **DO_S2** (BOOL): Aktiviert die Ausgabe für **State_02**.  
- **DO_S3** (BOOL): Aktiviert die Ausgabe für **State_03**.  
- **DO_S4** (BOOL): Aktiviert die Ausgabe für **State_04**.  

### **Adapter**  

- Keine Adapter vorhanden.  

## Funktionsweise  

1. **Initialisierung**: Beim Start befindet sich der Baustein im Zustand **xSTART**.  
2. **Sequenzstart**: Durch das Ereignis **START_S1** wechselt der Baustein zu **State_01** und aktiviert **DO_S1**.  
3. **Zustandsübergänge**:  
   - **S1_S2**: Wechsel zu **State_02** (aktiviert **DO_S2**, deaktiviert **DO_S1**).  
   - **S2_S3**: Wechsel zu **State_03** (aktiviert **DO_S3**, deaktiviert **DO_S2**).  
   - **S3_S4**: Wechsel zu **State_04** (aktiviert **DO_S4**, deaktiviert **DO_S3**).  
   - **S4_S1**: Zyklischer Rückkehr zu **State_01** (aktiviert **DO_S1**, deaktiviert **DO_S4**).  
4. **Reset-Funktion**: Das Ereignis **RESET** unterbricht die Sequenz und bringt den Baustein zurück zu **xSTART**, wobei alle Ausgaben deaktiviert werden.  

## Technische Besonderheiten  

- **Zyklischer Betrieb**: Der Übergang von **State_04** zu **State_01** ermöglicht eine endlose Wiederholung der Sequenz.  
- **Konsistente Zustandsverwaltung**: Jeder Zustand hat klare Eintritts- (**_E**), Austritts- (**_X**) und Bestätigungsalgorithmen (**_C**).  
- **Robuste Reset-Logik**: Der **RESET**-Zustand deaktiviert alle Ausgaben und setzt die Zustandsnummer zurück.  

## Zustandsübersicht  

1. **xSTART**: Initialzustand, keine aktiven Ausgaben.  
2. **sState_01**: Aktiviert **DO_S1**.  
3. **sState_02**: Aktiviert **DO_S2**, deaktiviert **DO_S1**.  
4. **sState_03**: Aktiviert **DO_S3**, deaktiviert **DO_S2**.  
5. **sState_04**: Aktiviert **DO_S4**, deaktiviert **DO_S3**.  
6. **sRESET**: Zwischenzustand für den Reset, deaktiviert alle Ausgaben und bestätigt den Rückkehr zum Startzustand.  

## Anwendungsszenarien  

- **Produktionsautomation**: Steuerung von Maschinen mit zyklischen Arbeitsabläufen (z. B. Förderbänder).  
- **Testsequenzen**: Wiederholte Ausführung von Testschritten in der Qualitätssicherung.  
- **Periodische Prozesse**: Steuerung von Anlagen mit regelmäßigen Wartungs- oder Reinigungszyklen.  

## Vergleich mit ähnlichen Bausteinen  

- **Vorteile gegenüber sequence_E_04**:  
  - Endlose Wiederholung der Sequenz ohne manuelle Rückführung.  
  - Einfache Integration in zyklische Prozesse.  
- **Nachteile**:  
  - Keine dynamische Anpassung der Zustandsreihenfolge.  
  - Begrenzt auf vier Zustände.  

## Fazit  

Der **sequence_E_04_loop**-Baustein ist eine optimierte Variante für zyklische Anwendungen, die eine wiederholte Abfolge von Zuständen erfordern.
Durch die klare Ereignissteuerung und robuste Reset-Funktion eignet er sich ideal für industrielle Automatisierungsaufgaben.
Für komplexere Szenarien mit variabler Zustandslogik könnten jedoch erweiterte Bausteine erforderlich sein.
