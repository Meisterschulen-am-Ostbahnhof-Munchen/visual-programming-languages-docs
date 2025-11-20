# sequence_E_05_loop

![sequence_E_05_loop](https://github.com/user-attachments/assets/a362ea33-3f0c-468c-a803-7da6c65cc599)

* * * * * * * * * *  

## Einleitung  

Der Funktionsbaustein **sequence_E_05_loop** ist eine **zyklische Erweiterung** von **sequence_E_05**, die eine endlose Wiederholung einer **fünfstufigen Zustandssequenz** ermöglicht.
Durch den Übergang vom letzten Zustand (**State_05**) zurück zum ersten Zustand (**State_01**) eignet sich dieser Baustein ideal für periodische Prozesse wie Produktionszyklen oder kontinuierliche Testabläufe.  

---

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  

| Ereignis       | Beschreibung                                      |  
|----------------|--------------------------------------------------|  
| **START_S1**   | Wechsel vom Startzustand (**xSTART**) zu **State_01**. |  
| **S1_S2**      | Wechsel von **State_01** zu **State_02**.        |  
| **S2_S3**      | Wechsel von **State_02** zu **State_03**.        |  
| **S3_S4**      | Wechsel von **State_03** zu **State_04**.        |  
| **S4_S5**      | Wechsel von **State_04** zu **State_05**.        |  
| **S5_S1**      | **Zyklischer Übergang** von **State_05** zu **State_01**. |  
| **RESET**      | Setzt die Zustandsmaschine von **jedem Zustand** zurück zu **xSTART**. |  

### **Ereignis-Ausgänge**  

| Ereignis  | Beschreibung                                      | Zugehörige Variable |  
|-----------|--------------------------------------------------|---------------------|  
| **CNF**   | Bestätigt die Ausführung eines Zustandswechsels. | `STATE_NR`          |  
| **EO_S1** | Wird bei Aktivierung von **State_01** ausgelöst. | `DO_S1`             |  
| **EO_S2** | Wird bei Aktivierung von **State_02** ausgelöst. | `DO_S2`             |  
| **EO_S3** | Wird bei Aktivierung von **State_03** ausgelöst. | `DO_S3`             |  
| **EO_S4** | Wird bei Aktivierung von **State_04** ausgelöst. | `DO_S4`             |  
| **EO_S5** | Wird bei Aktivierung von **State_05** ausgelöst. | `DO_S5`             |  

### **Daten-Ausgänge**  

| Variable     | Typ   | Beschreibung                                      |  
|-------------|-------|--------------------------------------------------|  
| **STATE_NR** | SINT  | Aktuelle Zustandsnummer (0 = Start, 1–5 = State_01–State_05). |  
| **DO_S1**    | BOOL  | Ausgabe für **State_01** (TRUE = aktiv).         |  
| **DO_S2**    | BOOL  | Ausgabe für **State_02** (TRUE = aktiv).         |  
| **DO_S3**    | BOOL  | Ausgabe für **State_03** (TRUE = aktiv).         |  
| **DO_S4**    | BOOL  | Ausgabe für **State_04** (TRUE = aktiv).         |  
| **DO_S5**    | BOOL  | Ausgabe für **State_05** (TRUE = aktiv).         |  

### **Adapter**  
- Keine Adapter vorhanden.  

---

## Funktionsweise  

1. **Initialisierung**:  
   - Der Baustein startet im Zustand **xSTART** (keine aktiven Ausgaben).  
2. **Sequenzstart**:  
   - Durch **START_S1** wird **State_01** aktiviert (`DO_S1 = TRUE`).  
3. **Zustandsübergänge**:  
   - Jeder Zustand aktiviert seine Ausgabe (`DO_Sx`) und deaktiviert die vorherige (`DO_Sx-1`).  
   - Beispiel: **S2_S3** wechselt zu **State_03** (aktiviert `DO_S3`, deaktiviert `DO_S2`).  
4. **Zykluslogik**:  
   - **S5_S1** springt **direkt zurück zu State_01** (aktiviert `DO_S1`, deaktiviert `DO_S5`).  
5. **Reset-Funktion**:  
   - **RESET** unterbricht die Sequenz und setzt alle Ausgaben zurück (`DO_S1–DO_S5 = FALSE`).  

---

## Technische Besonderheiten  

- **Zyklische Wiederholung**:  
  - Der Übergang **S5_S1** ersetzt **S5_START** (von **sequence_E_05**) und ermöglicht eine **endlose Schleife**.  
- **Konsistente Zustandsverwaltung**:  
  - Jeder Zustand hat klare Eintritts- (`_E`), Austritts- (`_X`) und Bestätigungsalgorithmen (`_C`).  
- **Robuste Reset-Logik**:  
  - Der **sRESET**-Zustand deaktiviert **alle Ausgaben** und setzt `STATE_NR` auf 0.  

---

## Zustandsübersicht  

| Zustand      | Aktivierte Ausgabe | Deaktivierte Ausgabe | Bemerkung                     |  
|--------------|--------------------|----------------------|-------------------------------|  
| **START**   | –                  | –                    | Initialzustand.               |  
| **State_01**| `DO_S1`            | `DO_S5` (bei S5_S1)  | Erster Prozessschritt.        |  
| **State_02**| `DO_S2`            | `DO_S1`              | Zweiter Prozessschritt.       |  
| **State_03**| `DO_S3`            | `DO_S2`              | Dritter Prozessschritt.       |  
| **State_04**| `DO_S4`            | `DO_S3`              | Vierter Prozessschritt.       |  
| **State_05**| `DO_S5`            | `DO_S4`              | Fünfter Prozessschritt.       |  
| **RESET**   | –                  | Alle (`DO_S1–DO_S5`) | Globaler Reset.               |  

---

## Anwendungsszenarien  

- **Kontinuierliche Produktion**: Steuerung von Maschinen mit **endlosen Arbeitszyklen** (z. B. Förderbänder, Verpackungsanlagen).  
- **Testautomation**: Wiederholte Ausführung von **5-stufigen Testsequenzen** ohne manuelle Rückstellung.  
- **Energiemanagement**: Zyklische Aktivierung von Verbrauchern in einem Netzwerk.  

---

## Vergleich mit sequence_E_05  

| Feature               | sequence_E_05       | sequence_E_05_loop      |  
|-----------------------|---------------------|-------------------------|  
| **Zyklusende**        | Rückkehr zu xSTART  | Direkt zu State_01      |  
| **Reset-Logik**       | Identisch           | Identisch               |  
| **Flexibilität**      | Einmaliger Durchlauf| Endlose Wiederholung    |  

**Vorteile von sequence_E_05_loop**:  
- Kein manueller Neustart der Sequenz erforderlich.  
- Ideal für **periodische Prozesse**.  

**Nachteile**:  
- Nicht geeignet für Anwendungen mit explizitem Sequenzende.  

---

## Fazit  

Der **sequence_E_05_loop**-Baustein ist die optimale Wahl für **zyklische 5-stufige Prozesse**, bei denen eine **kontinuierliche Wiederholung** benötigt wird.
Durch die klare Ereignissteuerung und robuste Reset-Funktion ist er besonders geeignet für industrielle Automatisierungslösungen.  

> **Hinweis**: Für einmalige Abläufe sollte **sequence_E_05** verwendet werden.
