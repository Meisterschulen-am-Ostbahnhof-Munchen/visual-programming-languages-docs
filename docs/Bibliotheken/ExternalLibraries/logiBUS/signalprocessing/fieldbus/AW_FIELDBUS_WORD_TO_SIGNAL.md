# AW_FIELDBUS_WORD_TO_SIGNAL


![AW_FIELDBUS_WORD_TO_SIGNAL](./AW_FIELDBUS_WORD_TO_SIGNAL.svg)

* * * * * * * * * *  

## Einleitung  
Der Funktionsbaustein **AW_FIELDBUS_WORD_TO_SIGNAL** dient als Filter für Feldbus-Wörter. Er spiegelt das eingehende Signal (über den Adapter **IN**) auf den Ausgang (Adapter **OUT**), sofern das Signal als gültig erkannt wurde. Die Gültigkeit wird über einen separaten Ausgangsadapter (**VALID**) signalisiert. Eingesetzt wird der Baustein typischerweise in Feldbus-Umgebungen, um nur valide Datenwerte an nachfolgende Komponenten weiterzuleiten.

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  
*Keine separaten Ereignis-Eingänge vorhanden.*  
Die Ereignissteuerung erfolgt implizit über die verwendeten Adapter (siehe Abschnitt **Adapter**).

### **Ereignis-Ausgänge**  
*Keine separaten Ereignis-Ausgänge vorhanden.*  
Die Ereignisausgabe erfolgt implizit über die Adapter.

### **Daten-Eingänge**  
*Keine separaten Daten-Eingänge vorhanden.*  
Die Datenübergabe erfolgt über die angeschlossenen Adapter.

### **Daten-Ausgänge**  
*Keine separaten Daten-Ausgänge vorhanden.*  
Die Datenausgabe erfolgt über die angeschlossenen Adapter.

### **Adapter**  

| Name | Typ | Beschreibung |
|------|-----|--------------|
| **IN** | `adapter::types::unidirectional::AW` (Socket) | Eingang des zu filternden Wortes. |
| **OUT** | `adapter::types::unidirectional::AW` (Plug) | Ausgang des gefilterten Wortes (nur bei gültigem Signal). |
| **VALID** | `adapter::types::unidirectional::AX` (Plug) | Gibt den Gültigkeitsstatus des Ausgangssignals aus (`TRUE` = gültig). |

## Funktionsweise  
Der Baustein besteht intern aus zwei Sub-Funktionsbausteinen: `FIELDBUS_WORD_TO_SIGNAL` und `E_D_FF` (D-Flip-Flop).  

- Ein eingehendes Ereignis auf `IN.E1` triggert die Verarbeitung des aktuellen Wortes über `FIELDBUS_WORD_TO_SIGNAL.REQ`.  
- Der Sub-Baustein `FIELDBUS_WORD_TO_SIGNAL` prüft die Gültigkeit des Wortes und gibt nach Abschluss ein `CNF`-Ereignis aus.  
- Dieses `CNF`-Ereignis bewirkt:
  - Das gefilterte Wort wird über `OUT.D1` an den Ausgangsadapter übergeben und über `OUT.E1` ausgegeben.
  - Gleichzeitig wird das D-Flip-Flop (`E_D_FF`) getaktet: Der aktuelle Gültigkeitsstatus (`VALID`‑Signal von `FIELDBUS_WORD_TO_SIGNAL`) wird übernommen.  
- Der Ausgang des Flip-Flops (`Q`) wird über `VALID.D1` und das Ereignis `VALID.E1` (ausgelöst durch `E_D_FF.EO`) an den Adapter **VALID** weitergegeben.

Somit wird nur dann ein gültiges Wort ausgegeben, wenn die interne Prüfung des eingehenden Signals erfolgreich ist. Der Gültigkeitsstatus bleibt bis zur nächsten Verarbeitung erhalten.

## Technische Besonderheiten  
- Der Baustein basiert vollständig auf Adaptern und hat keine separate Event‑/Data‑Schnittstelle auf oberster Ebene.  
- Die interne Realisierung verwendet einen standardisierten Feldbus‑Verarbeitungsbaustein (`FIELDBUS_WORD_TO_SIGNAL`) und ein D‑Flip‑Flop, was eine klare Trennung von Datenpfad und Statuslogik ermöglicht.  
- Die Implementierung ist unter der **Eclipse Public License 2.0** lizenziert.

## Zustandsübersicht  
Der Baustein selbst besitzt keinen expliziten Zustandsautomaten. Der innere Zustand wird durch das D‑Flip‑Flop repräsentiert:

| Zustand | Bedeutung |
|---------|-----------|
| `VALID = FALSE` | Der Ausgangswert ist ungültig (alte Daten oder Initialzustand). |
| `VALID = TRUE`  | Der Ausgangswert ist gültig und wurde beim letzten Verarbeitungszyklus als valide erkannt. |

## Anwendungsszenarien  
- **Feldbus‑Datenfilterung**: In Automatisierungssystemen, bei denen nur gültige Messwerte oder Steuerbefehle an nachfolgende Logik weitergegeben werden sollen.  
- **Signalvalidierung**: Einsatz in sicherheitskritischen Pfaden, wo ungültige Daten (z. B. aufgrund von Übertragungsfehlern) nicht ungeprüft weitergeleitet werden dürfen.  
- **Adapterbasierte Schnittstellen**: Geeignet für modulare Systeme, die über standardisierte Adapter kommunizieren (z. B. logiBUS‑Umgebung).

## Vergleich mit ähnlichen Bausteinen  
- Einfache **Word‑to‑Signal**‑Bausteine ohne Validierung geben das Eingangssignal direkt weiter, unabhängig von dessen Gültigkeit.  
- Der **AW_FIELDBUS_WORD_TO_SIGNAL** bietet im Gegensatz dazu eine explizite Gültigkeitsrückmeldung und unterdrückt ungültige Werte.  
- Andere Filterbausteine könnten zusätzliche Konfigurationsmöglichkeiten (z. B. Schwellwerte, Zeitfenster) enthalten, während dieser Baustein auf eine reine „gültig / ungültig“‑Entscheidung reduziert ist.

## Fazit  
Der AW_FIELDBUS_WORD_TO_SIGNAL ist ein spezialisierter Filterbaustein für Feldbus‑Wortdaten. Er kombiniert eine einfache Durchschleifung mit einer Gültigkeitsprüfung und stellt das Ergebnis über separate Adapter bereit. Durch die Verwendung von Standard‑Subbausteinen und Flip‑Flop‑Logik ist er robust, nachvollziehbar und gut in adapterbasierte Architekturen integrierbar.