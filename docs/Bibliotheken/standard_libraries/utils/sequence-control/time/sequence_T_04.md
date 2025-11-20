# sequence_T_04  

![sequence_T_04](https://github.com/user-attachments/assets/07646e44-93a6-4a5d-ae82-cf87704a4146)

* * * * * * * * * *  

## Einleitung  

Der Funktionsbaustein **sequence_T_04** ist eine **zeitgesteuerte** Zustandsmaschine mit **4 Ausgängen**, die automatische Zustandsübergänge nach konfigurierbaren Zeitintervallen ermöglicht.
Im Gegensatz zu ereignisgesteuerten Varianten (wie sequence_E_04) erfolgen die Übergänge hier zeitbasiert, was den Baustein ideal für Prozesse mit festen Zeitabläufen macht, z. B. in Produktionsstraßen oder Temperaturregelungen.  

---

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  

| Ereignis       | Beschreibung                                      | Mitgeführte Daten           |  
|----------------|--------------------------------------------------|-----------------------------|  
| **START_S1**   | Startet die Sequenz (xSTART → State_01)          | DT_S1_S2, DT_S2_S3, DT_S3_S4, DT_S4_START |  
| **RESET**      | Setzt alle Zustände zurück (→ xSTART)            | –                           |  

### **Ereignis-Ausgänge**  

| Ereignis  | Beschreibung                     | Zugehörige Variable |  
|-----------|----------------------------------|---------------------|  
| **CNF**   | Bestätigt Zustandswechsel        | `STATE_NR`          |  
| **EO_S1** | Aktivierung von **State_01**     | `DO_S1`             |  
| **EO_S2** | Aktivierung von **State_02**     | `DO_S2`             |  
| **EO_S3** | Aktivierung von **State_03**     | `DO_S3`             |  
| **EO_S4** | Aktivierung von **State_04**     | `DO_S4`             |  

### **Daten-Eingänge (Zeitparameter)**  

| Variable      | Typ   | Beschreibung                          | Initialwert          |  
|--------------|-------|--------------------------------------|----------------------|  
| **DT_S1_S2** | TIME  | Dauer von State_01 zu State_02       | `sequence::NO_TIME` |  
| **DT_S2_S3** | TIME  | Dauer von State_02 zu State_03       | `sequence::NO_TIME` |  
| **DT_S3_S4** | TIME  | Dauer von State_03 zu State_04       | `sequence::NO_TIME` |  
| **DT_S4_START** | TIME | Dauer von State_04 zurück zu xSTART  | `sequence::NO_TIME` |  

### **Daten-Ausgänge**  

| Variable     | Typ   | Beschreibung                          |  
|-------------|-------|--------------------------------------|  
| **STATE_NR** | SINT  | Aktueller Zustand (0=Start, 1-4=State_01-04) |  
| **DO_S1**    | BOOL  | Ausgabe für State_01 (TRUE=aktiv)    |  
| **DO_S2**    | BOOL  | Ausgabe für State_02 (TRUE=aktiv)    |  
| **DO_S3**    | BOOL  | Ausgabe für State_03 (TRUE=aktiv)    |  
| **DO_S4**    | BOOL  | Ausgabe für State_04 (TRUE=aktiv)    |  

### **Adapter**  

| Adapter     | Typ        | Beschreibung                          |  
|-------------|------------|--------------------------------------|  
| **timeOut** | `ATimeOut` | Steuert die zeitbasierten Übergänge  |  

---

## Funktionsweise  

1. **Initialisierung**:  
   - Der Baustein startet im Zustand **xSTART** (alle Ausgaben inaktiv).  
2. **Sequenzstart**:  
   - **START_S1** triggert den Übergang zu **State_01** und übergibt die Zeitparameter.  
   - `DO_S1` wird aktiviert, der Timer für den nächsten Zustand (**DT_S1_S2**) gestartet.  
3. **Automatische Übergänge**:  
   - Jeder Zustand aktiviert seine Ausgabe und startet einen Timer für den nächsten Übergang.  
   - Beispiel: Nach Ablauf von **DT_S1_S2** wechselt der Baustein zu **State_02** (`DO_S2=TRUE`, `DO_S1=FALSE`).  
4. **Sequenzende**:  
   - Nach **State_04** kehrt der Baustein nach **DT_S4_START** automatisch zu **xSTART** zurück.  
5. **Reset-Funktion**:  
   - **RESET** stoppt alle Timer, deaktiviert alle Ausgaben und setzt den Zustand auf **xSTART**.  

---

## Technische Besonderheiten  

- **Zeitgesteuerte Logik**:  
  - Alle Übergänge werden durch den **timeOut**-Adapter ausgelöst.  
  - Die Zeiten werden bei **START_S1** übergeben und in den Zuständen konfiguriert.  
- **Robuste Timer-Verwaltung**:  
  - Timer werden beim Zustandswechsel automatisch gestoppt/neu gestartet.  
- **Flexible Zeitparameter**:  
  - Jeder Übergang kann individuell konfiguriert werden (`NO_TIME` deaktiviert den automatischen Übergang).  

---

## Zustandsübersicht  

| Zustand      | Aktivierte Ausgabe | Timer-Parameter    | Übergangsbedingung       |  
|--------------|--------------------|--------------------|--------------------------|  
| **xSTART**   | –                  | –                  | START_S1                 |  
| **sState_01**| `DO_S1`            | `DT_S1_S2`         | `timeOut.TimeOut`        |  
| **sState_02**| `DO_S2`            | `DT_S2_S3`         | `timeOut.TimeOut`        |  
| **sState_03**| `DO_S3`            | `DT_S3_S4`         | `timeOut.TimeOut`        |  
| **sState_04**| `DO_S4`            | `DT_S4_START`      | `timeOut.TimeOut`        |  
| **sState_00**| –                  | –                  | –                        |  
| **sRESET**   | –                  | Stoppt alle Timer  | Sofortiger Übergang       |  

---

## Anwendungsschenarien  

- **Produktionsautomation**: Steuerung von Maschinen mit festen Taktzeiten.  
- **Temperaturregelung**: Zeitgesteuerte Phasen in Heiz-/Kühlprozessen.  
- **Testsequenzen**: Automatisierte Tests mit vordefinierten Wartezeiten.  

---

## Vergleich mit sequence_E_04  

| Feature               | sequence_E_04       | sequence_T_04          |  
|-----------------------|---------------------|------------------------|  
| **Übergangsart**      | Ereignisgesteuert   | Zeitgesteuert          |  
| **Flexibilität**      | Manuelle Steuerung  | Automatische Abläufe   |  
| **Reset-Logik**       | Identisch           | Identisch              |  

**Vorteile von sequence_T_04**:  
- Automatische Abläufe ohne externe Trigger.  
- Ideal für Prozesse mit festen Zeitvorgaben.  

**Nachteile**:  
- Keine manuelle Steuerung der Übergänge möglich.  

---

## Fazit  

Der **sequence_T_04**-Baustein ist die optimale Wahl für **zeitkritische Automatisierungsprozesse**, die präzise, wiederholbare Abläufe erfordern.
Durch die Integration des **timeOut**-Adapters und die flexible Konfiguration der Zeitparameter eignet er sich besonders für industrielle Anwendungen mit festen Taktzeiten.  

> **Hinweis**: Für manuell gesteuerte Prozesse sollte **sequence_E_04** verwendet werden.
