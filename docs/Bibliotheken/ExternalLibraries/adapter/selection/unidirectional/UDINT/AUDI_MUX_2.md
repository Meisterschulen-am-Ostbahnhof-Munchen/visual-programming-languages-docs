# AUDI_MUX_2


![AUDI_MUX_2](./AUDI_MUX_2.svg)

* * * * * * * * * *

## Einleitung

Der **AUDI_MUX_2** ist ein generischer Multiplexer-Funktionsblock (FB) gemäß IEC 61499. Er ermöglicht die Auswahl eines von zwei eingehenden Werten über einen Index (K) und leitet den ausgewählten Wert an den Ausgang weiter. Der FB ist als generischer Baustein (Generic FB) realisiert, sodass der konkrete Datentyp der Werte durch die Verwendung von Adaptern flexibel festgelegt werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar | Mit Daten |
|------|-----|-----------|-----------|
| REQ | Event | Set Index K | K |

Der Ereigniseingang `REQ` triggert die Verarbeitung. Der über `K` übergebene Index bestimmt, welcher der beiden Eingangswerte an den Ausgang weitergeleitet wird.

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF | Event | Confirmation of Set Index K |

Nach erfolgreicher Auswahl und Weiterleitung des Wertes wird das Ereignis `CNF` ausgegeben.

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K | UINT | Index (0 oder 1) |

Der Index `K` legt fest, welcher der beiden über die Adapter-Schnittstellen bereitgestellten Werte ausgewählt wird:
- **K = 0** → Wert von `IN1`
- **K = 1** → Wert von `IN2`

### **Daten-Ausgänge**

Dieser FB besitzt keine dedizierten Daten-Ausgänge. Die Ausgabe erfolgt ausschließlich über den Adapter `OUT`.

### **Adapter**

| Typ | Richtung | Bezeichner | Kommentar |
|-----|----------|------------|-----------|
| „adapter::types::unidirectional::AUDI“ | Plug | OUT | Ausgang: liefert den ausgewählten Wert |
| „adapter::types::unidirectional::AUDI“ | Socket | IN1 | Eingang 1: Wert für K=0 |
| „adapter::types::unidirectional::AUDI“ | Socket | IN2 | Eingang 2: Wert für K=1 |

Alle Adapter sind vom Typ `adapter::types::unidirectional::AUDI`. Dieser generische Adapter definiert eine unidirektionale Datenverbindung und kann im konkreten Projekt mit einem beliebigen Datentyp belegt werden (z. B. Integer, Real, Struktur). Dadurch wird der Baustein wiederverwendbar für unterschiedlichste Anwendungen.

## Funktionsweise

Der FB arbeitet nach dem Multiplexer-Prinzip:

1. Ein eingehendes Ereignis `REQ` löst die Verarbeitung aus.
2. Der Index `K` wird ausgelesen. Er muss den Wert 0 oder 1 annehmen.
3. Abhängig von `K` wird der entsprechende Adapter-Socket `IN1` (K=0) oder `IN2` (K=1) aktiviert und dessen Datenwert auf den Plug `OUT` übertragen.
4. Nach erfolgreicher Übertragung wird ein `CNF`-Ereignis gesendet.

Die Übertragung erfolgt synchron im Zuge der Ereignisverarbeitung. Es ist sicherzustellen, dass an den Sockets `IN1` und `IN2` gültige Werte anliegen, bevor `REQ` gesendet wird.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB wird als generischer Typ (`GEN_AUDI_MUX`) deklariert. Dadurch kann er in verschiedenen Kontexten mit unterschiedlichen Datentypen eingesetzt werden, ohne dass eine separate Implementierung für jeden Typ erforderlich ist.
- **Adapter-basierte Schnittstelle**: Die Verwendung von Adaptern anstelle von festen Datenports ermöglicht eine flexible Kopplung mit anderen Bausteinen, die denselben Adaptertyp implementieren.
- **Indexbereich**: Der Index `K` ist als `UINT` deklariert, wird aber im Multiplexer auf die Werte 0 und 1 beschränkt. Werte außerhalb dieses Bereichs führen zu undefiniertem Verhalten (keine Fehlerbehandlung im FB).
- **Lizenz**: Der Baustein steht unter der Eclipse Public License 2.0 (EPL‑2.0) zur Verfügung.

## Zustandsübersicht

Der FB besitzt keinen expliziten Zustandsautomaten (ECC). Die Funktionalität ist rein ereignisgesteuert:

- **Warten auf REQ**: Der FB wartet auf ein Ereignis am Eingang `REQ`.
- **Verarbeitung**: Nach Eintreffen von `REQ` wird der Index ausgewertet und der entsprechende Wert weitergeleitet.
- **Ausgabe von CNF**: Sofort nach Abschluss der Weiterleitung wird `CNF` ausgegeben. Der FB kehrt in den Wartezustand zurück.

Ein interner Zustand wird nicht benötigt.

## Anwendungsszenarien

- **Auswahl zwischen zwei Messwerten**: In der Automatisierungstechnik kann der FB eingesetzt werden, um zwischen zwei Sensorwerten (z. B. Temperatur, Druck) umzuschalten, gesteuert durch einen Betriebsmodus.
- **Umschaltung von Datenquellen**: In Kommunikationssystemen wählt der FB zwischen zwei parallelen Datenströmen aus, abhängig von einem Steuersignal.
- **Parameterauswahl**: In Steuerungsanwendungen kann der FB verwendet werden, um unterschiedliche Parametersätze (als Strukturen) an einen nachfolgenden Algorithmus weiterzugeben.

## Vergleich mit ähnlichen Bausteinen

- **IEC 61499‑Standard MUX**: Der Standard-MUX arbeitet meist mit festen Datentypen und mehr als zwei Eingängen. `AUDI_MUX_2` ist speziell auf zwei Eingänge beschränkt, dafür aber generisch über Adapter realisiert.
- **Multi‑Adapter‑Selektor**: Ein generischer 2‑zu‑1‑Multiplexer mit Adaptern bietet die gleiche Grundfunktion, jedoch oft mit zusätzlichen Zuständen oder Fehlerbehandlung. `AUDI_MUX_2` ist minimalistisch gehalten und eignet sich für einfache Umschaltaufgaben ohne Nebenwirkungen.

## Fazit

Der `AUDI_MUX_2` ist ein kompakter, generischer Multiplexer-Funktionsblock für die Auswahl zwischen zwei Werten. Seine adapterbasierte Schnittstelle macht ihn flexibel einsetzbar, ohne auf spezifische Datentypen festgelegt zu sein. Die einfache Ereignissteuerung und das klare Funktionsprinzip ermöglichen eine unkomplizierte Integration in IEC 61499‑Anwendungen. Für Aufgaben, die nur eine binäre Auswahl benötigen, stellt er eine effiziente und wiederverwendbare Lösung dar.