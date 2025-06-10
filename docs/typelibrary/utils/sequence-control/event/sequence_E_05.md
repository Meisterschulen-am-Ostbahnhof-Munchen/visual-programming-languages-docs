# sequence_E_05  

![sequence_E_05](https://github.com/user-attachments/assets/aa596a83-3a4a-4744-b85f-795a0d23591b)

* * * * * * * * * *  

## Einleitung  

Der Funktionsbaustein **sequence_E_05** ist eine erweiterte Zustandsmaschine, die eine sequenzielle Abfolge von **fünf Zuständen** steuert.
Im Vergleich zu den Vorgängerversionen (**sequence_E_04** und **sequence_E_04_loop**) bietet dieser Baustein eine zusätzliche Prozessstufe (**State_05**), was ihn ideal für komplexere Steuerungsabläufe macht, z. B. in mehrstufigen Produktionsprozessen oder erweiterten Testsequenzen.  

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
| **S5_START**   | Wechsel von **State_05** zurück zum Startzustand (**xSTART**). |  
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
4. **Zyklusende**:  
   - **S5_START** bringt den Baustein zurück zu **xSTART** (deaktiviert `DO_S5`).  
5. **Reset-Funktion**:  
   - **RESET** unterbricht die Sequenz und setzt alle Ausgaben zurück (`DO_S1–DO_S5 = FALSE`).  

---

## Technische Besonderheiten  

- **Erweiterte Zustandslogik**:  
  - Fünf Zustände mit klaren Eintritts- (`_E`), Austritts- (`_X`) und Bestätigungsalgorithmen (`_C`).  
- **Robuste Reset-Logik**:  
  - Der **sRESET**-Zustand deaktiviert **alle Ausgaben** und setzt `STATE_NR` auf 0.  
- **Konsistente Ereignissteuerung**:  
  - Jeder Übergang wird durch ein dediziertes Ereignis ausgelöst.  

---

## Zustandsübersicht  

| Zustand      | Aktivierte Ausgabe | Deaktivierte Ausgabe | Bemerkung                     |  
|--------------|--------------------|----------------------|-------------------------------|  
| **xSTART**   | –                  | –                    | Initialzustand.               |  
| **sState_01**| `DO_S1`            | –                    | Erster Prozessschritt.        |  
| **sState_02**| `DO_S2`            | `DO_S1`              | Zweiter Prozessschritt.       |  
| **sState_03**| `DO_S3`            | `DO_S2`              | Dritter Prozessschritt.       |  
| **sState_04**| `DO_S4`            | `DO_S3`              | Vierter Prozessschritt.       |  
| **sState_05**| `DO_S5`            | `DO_S4`              | Fünfter Prozessschritt.       |  
| **sState_00**| –                  | `DO_S5`              | Rückkehr zum Startzustand.     |  
| **sRESET**   | –                  | Alle (`DO_S1–DO_S5`) | Globaler Reset.               |  

---

## Anwendungsszenarien  

- **Mehrstufige Produktionslinien**: Steuerung von Maschinen mit fünf Arbeitsschritten (z. B. Pressen, Lackieren, Montieren).  
- **Qualitätstests**: Schrittweise Prüfung von Produkten mit fünf Testkriterien.  
- **Energieverteilung**: Phasenweise Aktivierung von Verbrauchern in einem Netzwerk.  

---

## Vergleich mit ähnlichen Bausteinen  

| Feature               | sequence_E_04       | sequence_E_05          |  
|-----------------------|---------------------|------------------------|  
| **Anzahl Zustände**   | 4                   | 5                      |  
| **Reset-Logik**       | Deaktiviert 4 Ausg. | Deaktiviert 5 Ausg.     |  
| **Flexibilität**      | Gering              | Höher (mehr Stufen)     |  

**Vorteile von sequence_E_05**:  
- Mehr Prozessstufen für komplexe Abläufe.  
- Klare Skalierbarkeit durch zusätzlichen Zustand.  

**Nachteile**:  
- Höherer Speicherbedarf für Zustandsverwaltung.  

---

## Fazit  

Der **sequence_E_05**-Baustein ist eine leistungsstarke Erweiterung für Anwendungen, die eine **fünfstufige Sequenz** erfordern.
Durch seine konsistente Ereignissteuerung und robuste Reset-Funktion eignet er sich ideal für industrielle Automatisierungslösungen.
Für einfachere Prozesse kann jedoch die **sequence_E_04**-Variante ausreichend sein.  
