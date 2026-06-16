# AX_RF_TRIG


![AX_RF_TRIG](./AX_RF_TRIG.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AX_RF_TRIG** dient der Erkennung von steigenden und fallenden Flanken eines booleschen Signals. Er empfängt den Signalwert über einen Adapter und gibt bei einer Flankenänderung entsprechende Ereignisse aus. Der Baustein kapselt die Standardlogik der IEC‑61499 Flankenerkennung (E_RF_TRIG) und stellt sie über eine einheitliche Adapterschnittstelle bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine direkten Ereignis-Eingänge. Die Auslösung der Flankenerkennung erfolgt ereignisgetrieben über den angeschlossenen Adapter (siehe Adapter).

### **Ereignis-Ausgänge**

| Name | Kommentar |
|------|-----------|
| ER   | Bestätigung, dass eine steigende Flanke (0→1) erkannt wurde. |
| EF   | Bestätigung, dass eine fallende Flanke (1→0) erkannt wurde. |

### **Daten-Eingänge**
Keine direkten Dateneingänge. Der zu überwachende boolesche Wert wird über den Adapter bereitgestellt.

### **Daten-Ausgänge**
Keine Datenausgänge.

### **Adapter**

| Name | Typ | Kommentar |
|------|-----|-----------|
| QI   | adapter::types::unidirectional::AX | Empfängt den booleschen Wert, dessen Flanken überwacht werden sollen. Der Adapter stellt sowohl ein Ereignis (E1) als auch den Datenwert (D1) bereit. |

## Funktionsweise
Der Baustein verwendet intern den IEC‑61499 Standardbaustein **E_RF_TRIG**. Über den Adapter **QI** wird bei jedem eingehenden Ereignis der aktuelle boolesche Datenwert abgefragt. Tritt eine Änderung des Wertes auf, so erzeugt der interne Baustein ein Ereignis:

- **ER** bei einem Übergang von *false* nach *true* (steigende Flanke).
- **EF** bei einem Übergang von *true* nach *false* (fallende Flanke).

Ohne Flankenänderung werden keine Ausgangsereignisse gesendet.

## Technische Besonderheiten
- Der Baustein ist als reiner Adapter‑Wrapper realisiert. Er besitzt keine eigene Zustandsmaschine, sondern delegiert die gesamte Logik an den genormten **E_RF_TRIG**.
- Die Verwendung eines Adaptertyps (hier **AX**) ermöglicht eine lose Kopplung zwischen der Signalquelle und der Flankenerkennung. Der Adapter kann in verschiedenen Kontexten wiederverwendet werden.
- Es werden ausschließlich Ereignisausgänge bereitgestellt; der aktuelle Signalwert wird nicht als Datenausgang weitergegeben.

## Zustandsübersicht
Der Baustein besitzt keine explizit dargestellte Zustandsmaschine. Das Verhalten entspricht dem des internen **E_RF_TRIG**, der einen impliziten Zustand (letzter Wert) speichert. Im Wesentlichen lassen sich zwei Phasen unterscheiden:
1. **Warten auf steigende Flanke:** der letzte Wert war *false*; bei *true* wird ER ausgelöst.
2. **Warten auf fallende Flanke:** der letzte Wert war *true*; bei *false* wird EF ausgelöst.

## Anwendungsszenarien
- Überwachung von binären Sensorsignalen (z. B. Endschalter, Lichtschranken) in der Automatisierungstechnik.
- Auslösen von Aktionen bei Signalwechseln (z. B. Start/Stopp einer Maschine).
- Ereignisgesteuerte Verarbeitung von booleschen Zuständen in industriellen Steuerungen.

## Vergleich mit ähnlichen Bausteinen
- **E_RF_TRIG:** Der Standardbaustein der IEC 61499. **AX_RF_TRIG** kapselt diesen und bietet eine Adapterschnittstelle an, sodass die Signalquelle nicht direkt an den Baustein gebunden werden muss.
- **R_TRIG** / **F_TRIG:** Erkennen nur eine Flankenrichtung. **AX_RF_TRIG** erkennt beide Richtungen und gibt entsprechende Ereignisse aus.
- **Adapter‑basierte Alternativen:** Andere Adaptertypen mit ähnlicher Semantik können ebenfalls zur Flankenerkennung verwendet werden, sofern sie den booleschen Wert und ein Ereignis bereitstellen.

## Fazit
Der Funktionsbaustein **AX_RF_TRIG** stellt eine praktische, adaptergestützte Lösung zur Erkennung beider Flanken eines booleschen Signals dar. Durch die Verwendung des Standardbausteins **E_RF_TRIG** ist die Funktion robust und normenkonform. Die Adapterschnittstelle erleichtert die Integration in modulare Systeme, bei denen Signalquellen und Verarbeitungslogik entkoppelt werden sollen.