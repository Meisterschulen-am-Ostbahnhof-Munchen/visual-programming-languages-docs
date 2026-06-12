# AW_TO_AL


![AW_TO_AL](./AW_TO_AL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein AW_TO_AL ist ein zusammengesetzter Baustein zur Umwandlung eines WORD-Adapters (AW) in einen LWORD-Adapter (AL). Er wird verwendet, um Daten von einem 16-Bit-Format in ein 64-Bit-Format zu überführen, typischerweise in Steuerungs- und Automatisierungssystemen. Der Baustein leitet Ereignisse und Daten direkt von der Eingangsseite zur Ausgangsseite weiter und sorgt dabei für die Typanpassung.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine (Ereignisse werden ausschließlich über den Adapter AW_IN übertragen)
### **Ereignis-Ausgänge**
Keine (Ereignisse werden ausschließlich über den Adapter AL_OUT ausgegeben)
### **Daten-Eingänge**
Keine (Daten werden ausschließlich über den Adapter AW_IN empfangen)
### **Daten-Ausgänge**
Keine (Daten werden ausschließlich über den Adapter AL_OUT gesendet)
### **Adapter**
- **AW_IN** (Socket): Adapter vom Typ `adapter::types::unidirectional::AW` – WORD-Eingang (16 Bit) mit Ereignis- und Datenkanal (E1, D1).
- **AL_OUT** (Plug): Adapter vom Typ `adapter::types::unidirectional::AL` – LWORD-Ausgang (64 Bit) mit Ereignis- und Datenkanal (E1, D1).

## Funktionsweise
Der Baustein realisiert eine einfache Durchschaltung: Das vom AW_IN-Adapter empfangene Ereignis (E1) wird direkt auf den Ereignisausgang AL_OUT.E1 weitergeleitet. Gleichzeitig wird das 16-Bit-Datensignal von AW_IN.D1 auf den 64-Bit-Datenausgang AL_OUT.D1 übertragen. Da der AL-Adapter LWORD erwartet, wird der WORD-Wert implizit in ein LWORD konvertiert (durch Null-Erweiterung oder explizite Typumwandlung gemäß der verwendeten Laufzeitumgebung). Der Baustein führt keine weiteren Operationen durch.

## Technische Besonderheiten
- Der Baustein ist als Composite-FB realisiert, d. h. er enthält ein internes Netzwerk, das die Adapter verbindet.
- Die Typkonvertierung von WORD zu LWORD erfolgt automatisch durch die Verkettung der Datenleitungen (implizite Typumwandlung).
- Ereignis- und Datenpfad sind synchron: Jedes eingehende Ereignis löst ein ausgehendes Ereignis aus, begleitet vom aktuellen Datenwert.
- Der Baustein ist unidirektional und unterstützt keine Rückwärtskommunikation.

## Zustandsübersicht
Da der Baustein keine eigene Zustandslogik besitzt, sondern nur eine Durchleitung realisiert, existieren keine expliziten Zustände. Die Funktion ist rein kombinatorisch bzw. ereignisgetrieben ohne Speicherverhalten.

## Anwendungsszenarien
- **Format‑Anpassung**: Wenn ein Sensor oder eine Steuerung nur WORD-Daten (16 Bit) liefert, das nachgelagerte System aber LWORD-Daten (64 Bit) erwartet, kann dieser Baustein zur Anpassung eingesetzt werden.
- **Adapterbrücke**: In Kommunikationsketten, in denen unterschiedliche Adaptertypen verwendet werden, ermöglicht der Baustein die nahtlose Integration.
- **Protokollkonvertierung**: Als Teil einer größeren Adapter-Kette für die Umstellung von 16-Bit auf 64-Bit Datenbusse.

## Vergleich mit ähnlichen Bausteinen
- **AW_TO_AW**: Identischer Typ, keine Konvertierung.
- **AL_TO_AW**: Rückwärtige Konvertierung von LWORD zu WORD (möglicherweise mit Datenverlust).
- **Direkte Verbindung ohne Konvertierung**: Wenn die Systeme denselben Adaptertyp verwenden, wird kein Konvertierungsbaustein benötigt.
- Der AW_TO_AL zeichnet sich durch seine Einfachheit und spezifische Typanpassung aus.

## Fazit
Der AW_TO_AL-Funktionsbaustein bietet eine unkomplizierte Möglichkeit, WORD-Daten in ein LWORD-Format zu überführen. Er eignet sich besonders für Szenarien, in denen eine reine Typanpassung ohne zusätzliche Logik erforderlich ist. Die Implementierung als Composite-FB gewährleistet eine transparente und effiziente Durchleitung.