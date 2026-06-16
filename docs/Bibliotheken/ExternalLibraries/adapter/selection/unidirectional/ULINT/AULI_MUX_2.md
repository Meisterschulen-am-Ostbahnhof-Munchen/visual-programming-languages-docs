# AULI_MUX_2


![AULI_MUX_2](./AULI_MUX_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AULI_MUX_2** realisiert einen digitalen Multiplexer (MUX) mit zwei Eingängen und einem Ausgang, die als unidirektionale AULI‑Adapter ausgeführt sind.  
Er wird verwendet, um abhängig von einem Indexwert **K** einen der beiden am Eingang anliegenden Datenströme an den Ausgang weiterzuleiten.  
Der Baustein ist als generischer Funktionsblock (GenericClassName: `GEN_AULI_MUX`) spezifiziert und eignet sich für Anwendungen, bei denen ein einfaches Umschalten zwischen zwei Signalquellen erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `REQ` | Event | Setzt den Index **K** und löst die Auswahl aus. |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `CNF` | Event | Bestätigt die Umschaltung nach Verarbeitung eines `REQ`-Ereignisses. |

### **Daten-Eingänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `K`   | UINT     | Auswahlindex (erwartet: 0 für IN1, 1 für IN2). |

### **Daten-Ausgänge**
Keine direkten Datenausgänge – der ausgegebene Wert wird über den Adapter `OUT` transportiert.

### **Adapter**

| Name | Typ (Adapter) | Richtung | Kommentar |
|------|----------------|----------|-----------|
| `OUT` | adapter::types::unidirectional::AULI | Plug | Ausgang des Multiplexers – liefert den Wert des gewählten Eingangs. |
| `IN1` | adapter::types::unidirectional::AULI | Socket | Erster Eingang (Auswahl bei K = 0). |
| `IN2` | adapter::types::unidirectional::AULI | Socket | Zweiter Eingang (Auswahl bei K = 1). |

## Funktionsweise
Der Funktionsblock arbeitet ereignisgesteuert:  
1. Ein `REQ`-Ereignis übernimmt den aktuellen Wert des Daten-Eingangs **K**.  
2. Der Baustein kopiert den Datenwert des Adapters `IN1` auf den Adapter `OUT`, falls **K = 0**, bzw. den Wert von `IN2` auf `OUT`, falls **K = 1**.  
3. Nach erfolgter Übertragung wird das `CNF`-Ereignis ausgegeben.  

Der Index **K** wird nur bei einem `REQ`-Ereignis gelesen; eine Änderung des Index ohne Ereignis hat keine unmittelbare Wirkung.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_AULI_MUX`) definiert, sodass er in verschiedenen Kontexten mit demselben Adapterprotokoll eingesetzt werden kann.  
- **Unidirektionale Adapter**: Alle Adapter sind als `unidirectional::AULI` spezifiziert – die Daten fließen nur vom Socket zum Plug.  
- **Keine Zustandsspeicherung**: Der Baustein besitzt keinen internen Zustandsautomaten; die Umschaltung erfolgt rein kombinatorisch auf das `REQ`-Ereignis hin.  
- **Minimale Latenz**: Durch die direkte Weiterleitung der Adapterdaten entsteht keine Verzögerung durch aufwändige Verarbeitung.

## Zustandsübersicht
Der FB besitzt keinen expliziten Zustandsautomaten. Er verhält sich wie eine ereignisgesteuerte Übertragungsfunktion:
- **Warten auf REQ** → Lesen von K, Weiterleiten des entsprechenden Eingangs, Ausgabe von CNF.  
- Systembedingte Wartezeiten können entstehen, wenn die angeschlossenen Adapter keine Daten bereitstellen (blockierendes Verhalten des AULI‑Protokolls).

## Anwendungsszenarien
- **Signalumschaltung**: Wahl zwischen zwei Sensoren, Messwerten oder Steuersignalen in der Automatisierungstechnik.  
- **Redundante Kanäle**: Aktivierung eines Reserveeingangs (IN2) bei Ausfall des primären Signals (IN1).  
- **Parametrierbare Datenquellen**: Auswahl verschiedener Datenströme durch übergeordnete Steuerungslogik (z. B. über einen Index aus einem HM‑Panel).  
- **Generische Umsetzung**: Der FB kann in SPS‑Bibliotheken als Grundbaustein für beliebige AULI‑Adaptersignale verwendet werden.

## Vergleich mit ähnlichen Bausteinen
- **`MUX_4`-Bausteine** (Vierfach-Multiplexer): Diese benötigen zwei Auswahlleitungen (K=0..3) und haben vier Eingangsadapter. `AULI_MUX_2` ist auf zwei Kanäle beschränkt, dafür einfacher und schneller.  
- **`SELECT` (IEC 61131‑3)**: Arbeitet auf elementaren Datentypen (BOOL, INT, …), während `AULI_MUX_2` über strukturierte Adapter kommuniziert und daher komplexe Datenobjekte übertragen kann.  
- **`MERGE`-Bausteine**: Diese kombinieren mehrere Eingänge parallel (z. B. Logik‑ODER), während der MUX exklusiv einen einzelnen Kanal durchschaltet.

## Fazit
Der Funktionsblock `AULI_MUX_2` stellt einen einfachen, aber robusten Multiplexer für den Einsatz in 4diac‑Umgebungen dar.  
Dank seiner generischen Definition und der ereignisgesteuerten Schnittstelle ist er flexibel einsetzbar und fügt sich nahtlos in Adapter‑basierte Kommunikationsstrukturen ein.  
Er eignet sich besonders für Anwendungen, in denen schnell und zuverlässig zwischen zwei Signalquellen umgeschaltet werden muss.