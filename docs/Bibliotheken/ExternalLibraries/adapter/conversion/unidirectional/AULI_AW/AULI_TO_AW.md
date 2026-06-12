# AULI_TO_AW


![AULI_TO_AW](./AULI_TO_AW.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AULI_TO_AW** ist ein zusammengesetzter Baustein (Composite FB), der eine ULINT‑Adapter-Schnittstelle (AULI) in eine WORD‑Adapter-Schnittstelle (AW) umwandelt. Er wird dort eingesetzt, wo ein unidirektionaler Datentyp‑Wechsel von vorzeichenloser 64‑Bit‑Ganzzahl auf 16‑Bit‑Wort erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| E1 (über AULI_IN) | Event | Startet die Konvertierung |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| E1 (über AW_OUT) | Event | Signalisiert die Fertigstellung der Konvertierung |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| D1 (über AULI_IN) | ULINT | ULINT‑Eingangswert |

### **Daten-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| D1 (über AW_OUT) | WORD | WORD‑Ausgangswert |

### **Adapter**

| Typ | Rolle | Name | Kommentar |
|-----|-------|------|-----------|
| **adapter::types::unidirectional::AULI** | Socket | AULI_IN | ULINT‑Adapter Eingang |
| **adapter::types::unidirectional::AW**   | Plug  | AW_OUT  | WORD‑Adapter Ausgang |

## Funktionsweise

Der Baustein verwendet intern die IEC‑61131‑Funktion **F_ULINT_TO_WORD**, um den ankommenden ULINT‑Wert (über den AULI_IN‑Adapter) in einen WORD‑Wert zu wandeln. Der Ablauf ist rein ereignisgesteuert:

1. Ein eingehendes Ereignis am AULI_IN‑Adapter (E1) triggert die Konvertierung.
2. Der ULINT‑Wert (D1) wird dem FB **F_ULINT_TO_WORD** übergeben.
3. Nach Abschluss der Wandlung wird das Ausgangsereignis am AW_OUT‑Adapter (E1) gesendet, und der WORD‑Wert steht am Ausgangsdatenpunkt (D1) zur Verfügung.

## Technische Besonderheiten

- **Unidirektionale Adapter**: Sowohl AULI_IN als auch AW_OUT sind unidirektionale Adapter, d.h. der Datenfluss erfolgt nur in eine Richtung.
- **Komposition**: Der Baustein ist aus einem einzigen integrierten Konvertierungs‑FB aufgebaut, was ihn leicht nachvollziehbar und wartbar macht.
- **Typkonvertierung**: Die Wandlung von ULINT (64‑Bit) nach WORD (16‑Bit) führt bei Werten größer als 65535 zu einem Überlauf – der Anwender muss sicherstellen, dass der Eingangswert im Bereich von 0…65535 liegt.

## Zustandsübersicht

Da es sich um einen reinen Composite‑FB ohne eigene Zustandsmaschine handelt, gibt es keine internen Zustände. Die gesamte Logik wird durch den eingebetteten FB **F_ULINT_TO_WORD** realisiert, der eine einfache, ereignisgesteuerte Funktionsausführung besitzt.

## Anwendungsszenarien

- **Schnittstellenanpassung**: Wenn ein AULI‑Adapter (z.B. von einer Sensor‑Einheit) in ein System eingebunden werden muss, das nur WORD‑Adapter‑Schnittstellen (AW) unterstützt.
- **Datenreduktion**: Reduzierung der Datenbreite von 64‑Bit auf 16‑Bit für nachfolgende Verarbeitungsschritte.
- **Legacy‑Integration**: Einbinden älterer Komponenten, die nur mit 16‑Bit‑Daten arbeiten, in eine moderne Umgebung, die ULINT liefert.

## Vergleich mit ähnlichen Bausteinen

Vergleichbare Bausteine sind z.B. **ULINT_TO_INT** oder **ULINT_TO_DWORD**, die andere Zielformate anbieten. **AULI_TO_AW** ist speziell auf die unidirektionalen Adapter‑Typen der 4diac‑Welt zugeschnitten. Im Unterschied zu einer einfachen Typkonvertierung übernimmt der Baustein auch die Ereignis‑ und Adapter‑Verknüpfung, was die Integration in Adapter‑basierte Architekturen erheblich vereinfacht.

## Fazit

**AULI_TO_AW** ist ein praktischer, kompakter Konvertierungsbaustein, der die Lücke zwischen ULINT‑ und WORD‑Adapter‑Schnittstellen schließt. Durch die Kapselung der IEC‑Funktion in einem Composite‑FB wird der Anwender von Adapter‑Details entlastet und erhält eine saubere, ereignisgesteuerte Transformationslösung. Der Baustein eignet sich besonders für Szenarien, in denen Datenbreiten reduziert und gleichzeitig die Adapter‑Struktur beibehalten werden soll.