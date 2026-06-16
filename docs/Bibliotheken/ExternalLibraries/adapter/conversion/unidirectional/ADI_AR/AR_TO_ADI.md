# AR_TO_ADI


![AR_TO_ADI](./AR_TO_ADI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AR_TO_ADI** ist ein Composite-Baustein, der einen REAL‑Adapter (AR) in einen DINT‑Adapter (ADI) umwandelt. Er wird verwendet, um zwischen Schnittstellen mit unterschiedlichen Datentypen zu vermitteln, wobei die Konvertierung ereignisgesteuert abläuft.

## Schnittstellenstruktur
Die Schnittstelle des Bausteins besteht ausschließlich aus Adaptern, die sowohl Ereignisse als auch Daten bündeln. Es sind keine separaten Ein‑ oder Ausgänge vorhanden.

### **Ereignis-Eingänge**
- **AR_IN.E1** – Ereigniseingang über den AR‑Adapter  
  Löst die Konvertierung des anliegenden REAL‑Wertes aus.

### **Ereignis-Ausgänge**
- **ADI_OUT.E1** – Ereignisausgang über den ADI‑Adapter  
  Wird nach erfolgreicher Konvertierung aktiviert.

### **Daten-Eingänge**
- **AR_IN.D1** (Datentyp REAL) – Der zu konvertierende Gleitkommawert.

### **Daten-Ausgänge**
- **ADI_OUT.D1** (Datentyp DINT) – Der konvertierte Ganzzahlwert.

### **Adapter**

| Adapter | Name | Richtung | Beschreibung |
|---------|------|----------|--------------|
| AR  | AR_IN | Socket (Eingang)  | Unidirektionaler REAL‑Adapter, der das Eingangssignal bereitstellt. |
| ADI | ADI_OUT | Plug (Ausgang) | Unidirektionaler DINT‑Adapter, der das konvertierte Signal weitergibt. |

## Funktionsweise
Der Baustein ist als Composite‑FB realisiert. Im Inneren befindet sich eine Instanz des IEC‑61131‑Standardbausteins `F_REAL_TO_DINT`.  
Sobald am Ereigniseingang **AR_IN.E1** ein Ereignis eintrifft, wird der über **AR_IN.D1** anliegende REAL‑Wert an den internen Konverter übergeben. Nach abgeschlossener Konvertierung wird das Ergebnis an **ADI_OUT.D1** weitergeleitet und das Ereignis **ADI_OUT.E1** ausgelöst.

## Technische Besonderheiten
- Der Baustein verwendet den Datentyp‑Konverter `F_REAL_TO_DINT` aus der IEC‑61131‑Bibliothek.
- Es handelt sich um einen Composite‑FB, der keine eigene Zustandslogik besitzt, sondern die Funktionalität durch den internen Baustein abbildet.
- Die Schnittstelle ist rein adapterbasiert, sodass eine einfache Einbindung in bestehende Adapter‑Netzwerke möglich ist.

## Zustandsübersicht
Da der FB keine Zustandsmaschine enthält, ergibt sich folgender einfacher Ablauf:

1. **Warten** – Der FB ist bereit, ein Ereignis auf **AR_IN.E1** zu empfangen.
2. **Konvertierung** – Sobald ein Ereignis eintrifft, wird der REAL‑Wert in DINT umgewandelt.
3. **Ausgabe** – Nach Abschluss der Konvertierung wird das Ergebnis ausgegeben und das Ausgangsereignis gesendet.<br>Danach kehrt der FB in den Wartezustand zurück.

## Anwendungsszenarien
- Anpassung einer Sensorik, die REAL‑Werte liefert, an eine Steuerung, die DINT‑Werte erwartet.
- Brücke zwischen zwei Adapter‑basierten Komponenten mit unterschiedlichen Datentypen in einem IEC‑61499‑System.
- Nutzung in Datenvorverarbeitungsketten, bei denen Gleitkommazahlen in Ganzzahlen umgerechnet werden müssen.

## Vergleich mit ähnlichen Bausteinen
- **`F_REAL_TO_DINT`** – Dieser Baustein führt die eigentliche Konvertierung durch, erwartet aber separate Ereignis‑ und Datenanschlüsse. **AR_TO_ADI** kapselt diese Funktionalität in einer adapterbasierten Schnittstelle und vereinfacht so die Einbindung in Adapter‑Netzwerke.
- **Andere Adapter‑Konverter** – Ähnliche Bausteine existieren für andere Datentypkombinationen (z.B. AR_TO_AINT, ADI_TO_AR). Alle folgen dem gleichen Muster: Verwendung eines internen Konvertierungs‑FBs, eingebettet in eine einheitliche Adapter‑Hülle.

## Fazit
**AR_TO_ADI** ist ein kompakter, wiederverwendbarer Composite‑FB, der eine saubere Umwandlung von REAL‑ auf DINT‑Adapter ermöglicht. Dank seiner einfachen, ereignisgesteuerten Struktur und der Nutzung standardisierter Konvertierungsbausteine eignet er sich hervorragend für Adapter‑basierte Entwürfe in industriellen Steuerungssystemen.