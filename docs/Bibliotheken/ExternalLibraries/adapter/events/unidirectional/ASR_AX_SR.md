# ASR_AX_SR

```{index} single: ASR_AX_SR
```

<img width="1139" height="229" alt="image" src="https://github.com/user-attachments/assets/d4c4cfae-6044-477d-a62f-71e94d0d34a2" />

* * * * * * * * * *
## Einleitung
Der ASR_AX_SR ist ein ereignisgesteuerter bistabiler Funktionsblock (Flip-Flop), der nach dem Set-Reset-Prinzip arbeitet. Er dient zur Speicherung eines binären Zustands und wird über Adapter-Schnittstellen angesteuert.

![ASR_AX_SR](ASR_AX_SR.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine direkten Ereigniseingänge vorhanden - die Steuerung erfolgt ausschließlich über Adapter.

### **Ereignis-Ausgänge**
Keine direkten Ereignisausgänge vorhanden - die Ausgabe erfolgt ausschließlich über Adapter.

### **Daten-Eingänge**
Keine direkten Dateneingänge vorhanden.

### **Daten-Ausgänge**
Keine direkten Datenausgänge vorhanden.

### **Adapter**
- **S_R (Socket)**: Set/Reset-Steueradapter vom Typ `adapter::types::unidirectional::ASR`
- **Q (Plug)**: Ausgabeadapter vom Typ `adapter::types::unidirectional::AX` für den Flip-Flop-Zustand

## Funktionsweise
Der ASR_AX_SR arbeitet als Set-Reset-Flip-Flop mit drei Zuständen:
- **START**: Initialzustand
- **SET**: Gesetzter Zustand (Q = TRUE)
- **RESET**: Rückgesetzter Zustand (Q = FALSE)

Bei einem SET-Ereignis über den S_R-Adapter wechselt der Block in den SET-Zustand und setzt den Ausgang Q auf TRUE. Bei einem RESET-Ereignis wechselt er in den RESET-Zustand und setzt Q auf FALSE.

## Technische Besonderheiten
- **Keine Priorisierung (Dominanz)**: Da das Setzen und Rücksetzen durch getrennte Ereignisse (`S_R.SET`, `S_R.RESET`) ausgelöst wird, gibt es keine gleichzeitige Dominanz wie in der IEC 61131-3. Der Zustand wird durch das zuletzt eingetroffene Ereignis bestimmt ("Last Event Wins").
- **Verwendung von Adaptern**: Verwendet unidirektionale Adapter für Ein- und Ausgabe (`ASR` für Set/Reset, `AX` für Ausgang).
- **Implementierung**: Realisiert als Basic Function Block mit explizitem Zustandsautomaten (ECC).
- **Schnittstelle**: Keine direkten Ein-/Ausgänge, ausschließlich Adapter-basierte Kommunikation.

## Zustandsübergänge
```
START → SET:    bei S_R.SET Ereignis
SET → RESET:    bei S_R.RESET Ereignis
RESET → SET:    bei S_R.SET Ereignis
```

## Algorithmen
- **SET**: Setzt den Ausgangswert Q.D1 auf TRUE
- **RESET**: Setzt den Ausgangswert Q.D1 auf FALSE

## Anwendungsszenarien
- Speicherung von Schaltzuständen in Steuerungsanwendungen
- Zustandsspeicherung in sequentiellen Ablaufsteuerungen
- Flip-Flop-Funktionalität in verteilten Automatisierungssystemen

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **[SR (IEC 61131-3)](../../../../Vergleich/IEC61131_3/SR_ALT.md)**: Der klassische SR-Baustein hat eine definierte Setz-Dominanz bei gleichzeitigen Signalen. Der `ASR_AX_SR` verhält sich dagegen zeitabhängig (letztes Ereignis zählt).
- **[E_SR](../../../../StandardLibraries/events/E_SR.md)**: Funktional ähnlich (ereignisgesteuert), aber mit direkten Event-Pins statt Adaptern.
- **Konventionelle Flip-Flops**: Im Vergleich zu Flip-Flops mit direkten Ein-/Ausgängen erleichtert das Adapter-Design die Integration in modulare Systemarchitekturen.




## 🛠️ Zugehörige Übungen

* [Uebung_171_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_171_AX.md)

## Fazit
Der ASR_AX_SR bietet eine saubere, adapter-basierte Implementierung eines bistabilen Speicherelements, das ideal für den Einsatz in modularen IEC 61499-Systemen geeignet ist. Die ausschließliche Verwendung von Adaptern ermöglicht eine hohe Flexibilität bei der Systemintegration.