# E_CTUD_UDINT  

![E_CTUD_UDINT](https://user-images.githubusercontent.com/116869307/214142444-55a16971-caf0-4c6c-a1fa-c0294a26464a.png)  

* * * * * * * * * *   

## Einleitung  
Der **E_CTUD_UDINT** ist ein erweiterter Zählbaustein nach IEC 61499, der sowohl Aufwärts- als auch Abwärtszählfunktionen mit dem Datentyp UDINT (unsigned double integer) unterstützt. Dieser Baustein kombiniert die Funktionalität eines hochpräzisen Zählers mit der Flexibilität ereignisgesteuerter Operationen.

---

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  
- `CU` (Count Up): Erhöht den Zählerstand um 1  
- `CD` (Count Down): Verringert den Zählerstand um 1  
- `R` (Reset): Setzt den Zähler auf 0 zurück  
- `LD` (Load): Lädt einen neuen vordefinierten Wert  

### **Ereignis-Ausgänge**  
- `CUO` (Count Up Overflow): Wird bei Überlauf ausgelöst  
- `CDO` (Count Down Underflow): Wird bei Unterlauf ausgelöst  
- `LDO` (Load Done): Bestätigt erfolgreiches Laden  

### **Daten-Ein-/Ausgänge**  
| Port | Typ   | Beschreibung                     |  
|------|-------|----------------------------------|  
| PV   | UDINT | Vorgabewert (Preset Value)       |  
| CV   | UDINT | Aktueller Zählerstand (Current Value) |  

---

## Funktionsweise  

1. **Zähloperationen**  
   - Bei jedem `CU`-Ereignis: `CV = CV + 1`  
   - Bei jedem `CD`-Ereignis: `CV = CV - 1`  

2. **Spezialfälle**  
   - **Überlauf**: Bei Erreichen von UDINT-Maximum → `CUO`  
   - **Unterlauf**: Bei Unterschreiten von 0 → `CDO`  

3. **Steuerfunktionen**  
   - `R` setzt `CV` sofort auf 0  
   - `LD` lädt `PV` in `CV` und triggert `LDO`  

---

## Technische Besonderheiten  

✔ **32-bit Unsigned Integer** (0 bis 4,294,967,295)  
✔ **Ereignisgesteuerte Logik** (kein zyklischer Aufruf nötig)  
✔ **Parallele Operationsmöglichkeit** (gleichzeitige CU/CD-Events)  

---

## Anwendungsszenarien  

- **Produktionsüberwachung**: Präzise Teilezählung  
- **Energiemanagement**: Verbrauchszählung  
- **Prozesssteuerung**: Zyklusüberwachung  

---

## Vergleich mit ähnlichen Bausteinen  

| Feature        | E_CTUD_UDINT | E_CTU | E_CTD |  
|---------------|-------------|-------|-------|  
| Zählrichtung  | Auf/Ab      | Auf   | Ab    |  
| Datentyp      | UDINT       | INT   | INT   |  
| Überlaufkontrolle | Ja      | Nein  | Nein  |  

---

## Fazit  

Der E_CTUD_UDINT-Baustein bietet industriellen Steuerungssystemen eine leistungsstarke Zähllösung mit:  
- Erweiterter Zahlenreichweite (32-bit)  
- Bidirektionaler Zählfunktion  
- Robuster Ereignissteuerung  

Durch seine präzise Steuerlogik und große Zählkapazität eignet er sich besonders für Hochleistungsanwendungen in automatisierten Produktionsumgebungen. Die strikte Ereignisorientierung macht ihn zudem ideal für verteilte Steuerungsarchitekturen nach IEC 61499.




















































































