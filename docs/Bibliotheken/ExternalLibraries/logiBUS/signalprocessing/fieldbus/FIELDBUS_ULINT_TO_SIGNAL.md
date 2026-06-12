# FIELDBUS_ULINT_TO_SIGNAL


![FIELDBUS_ULINT_TO_SIGNAL](./FIELDBUS_ULINT_TO_SIGNAL.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **FIELDBUS_ULINT_TO_SIGNAL** dient als Filterbaustein für Feldbussignale vom Typ `ULINT`. Er prüft, ob ein eingehender Wert innerhalb des gültigen Signalbereichs liegt und gibt diesen – je nach Ergebnis – entweder unverändert aus oder setzt den Ausgang auf einen definierten Ungültigkeitswert. Das VALID-Ausgangssignal zeigt den Status der Signalvalidität an.

Der Baustein ist besonders geeignet für den Einsatz in sicherheitskritischen oder qualitätsüberwachenden Applikationen, bei denen ungültige oder fehlerhafte Feldbuswerte zuverlässig erkannt und behandelt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| REQ      | Normaler Ausführungsanforderung – löst die Verarbeitung des Eingangswerts IN aus. Der Ereignisausgang CNF wird nach Abschluss der Aktion gesendet. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Bestätigung der Ausführung – wird nach der Berechnung von OUT und VALID gesendet. |

### **Daten-Eingänge**

| Name | Typ   | Initialwert                                    | Beschreibung |
|------|-------|------------------------------------------------|--------------|
| IN   | ULINT | `LWORD_TO_ULINT(NOT_AVAILABLE_LWM)` | Eingangssignal (Rohwert vom Feldbus) |

*Hinweis:* `NOT_AVAILABLE_LWM` ist eine aus der Bibliothek `FIELDBUS_SIGNAL` importierte Konstante, die einen ungültigen oder nicht verfügbaren Signalwert repräsentiert.

### **Daten-Ausgänge**

| Name  | Typ   | Initialwert               | Beschreibung |
|-------|-------|----------------------------|--------------|
| OUT   | ULINT | `16#0000000000000000`      | Gefilterter Ausgangswert – entspricht IN, wenn gültig, andernfalls 0. |
| VALID | BOOL  | `FALSE`                    | Signalvalidität – `TRUE` bei gültigem Eingang, sonst `FALSE`. |

### **Adapter**

Der Baustein besitzt keine Adapter-Schnittstellen.

## Funktionsweise

Nach einem Ereignis am Eingang **REQ** wird der folgende Algorithmus ausgeführt:

1. Prüfung: **IN** ≤ `LWORD_TO_ULINT(VALID_SIGNAL_LW)`  
   - `VALID_SIGNAL_LW` ist eine importierte Konstante aus der `FIELDBUS_SIGNAL`-Bibliothek und definiert die obere Grenze des gültigen Wertebereichs.

2. **Fall – Eingang gültig** (Bedingung erfüllt):  
   - `OUT` := `IN`  
   - `VALID` := `TRUE`

3. **Fall – Eingang ungültig** (Bedingung nicht erfüllt):  
   - `OUT` := `0`  
   - `VALID` := `FALSE`

Anschließend wird der Ereignisausgang **CNF** ausgelöst.

## Technische Besonderheiten

- Der Baustein arbeitet deterministisch und benötigt nur eine einzige Verarbeitungsstufe.
- Die Schwellwerte `NOT_AVAILABLE_LWM` und `VALID_SIGNAL_LW` sind als externe Konstanten definiert und zentral in der Bibliothek `FIELDBUS_SIGNAL` hinterlegt. Sie können ohne Änderung des Bausteins angepasst werden.
- Der Ausgangswert bei ungültigem Signal ist auf 0 gesetzt, was in vielen Feldbussystemen einen definierten „Ungültigkeitswert“ darstellt.
- Der initiale Wert von `IN` wird als „nicht verfügbar“ deklariert, sodass der Baustein auch ohne vorheriges Ereignis einen definierten Zustand liefert.

## Zustandsübersicht

Der Funktionsblock ist als **SimpleFB** realisiert und besitzt nur einen einzigen Zustand:

| Zustand | Beschreibung |
|---------|--------------|
| REQ     | Eingangszustand: Wartet auf Ereignis REQ. Bei Eintritt wird der Algorithmus `REQ` ausgeführt und anschließend der Ausgang `CNF` gesendet. Danach verbleibt der Baustein im selben Zustand. |

Es existieren keine weiteren Zustände oder Verzweigungen – die Funktionsweise ist rein ablauforientiert.

## Anwendungsszenarien

- **Feldbus-Signalaufbereitung:** Ein Sensor liefert einen ULINT-Wert, der nur innerhalb eines bestimmten Bereichs physikalisch sinnvoll ist (z. B. Drehzahl, Druck). Der Baustein filtert ungültige Messungen heraus.
- **Sicherheitskette:** In einer sicherheitsgerichteten Steuerung werden fehlerhafte oder abweichende Feldbuswerte erkannt und durch einen definierten Ersatzwert (0) ersetzt, gleichzeitig wird ein Gültigkeitssignal für die nachgeschaltete Logik bereitgestellt.
- **Qualitätsüberwachung:** Der VALID-Ausgang kann zur Überwachung der Datenintegrität verwendet werden, z. B. um Alarme auszulösen oder auf alternative Signalquellen umzuschalten.

## Vergleich mit ähnlichen Bausteinen

Im 4diac-Framework existieren weitere Filterbausteine für andere Datentypen, z. B. `FIELDBUS_DINT_TO_SIGNAL` oder `FIELDBUS_REAL_TO_SIGNAL`. Gemeinsam ist allen das Prinzip der Gültigkeitsprüfung mittels einer vordefinierten Obergrenze. Der vorliegende Baustein ist speziell auf den `ULINT`-Datentyp zugeschnitten, was einen effizienten und typsicheren Einsatz in Applikationen mit 64‑Bit‑unsigned‑Werten ermöglicht.

## Fazit

Der **FIELDBUS_ULINT_TO_SIGNAL** ist ein einfacher, aber zuverlässiger Funktionsblock zur Signalvalidierung im Feldbusumfeld. Durch die klare Trennung in gültige und ungültige Werte sowie die Bereitstellung eines BOOL‑Ausgangs für die Validität eignet er sich hervorragend für den Einsatz in modularen Automatisierungssystemen, bei denen Datenqualität und Fehlererkennung essenziell sind. Die Verwendung externer Konstanten erlaubt eine flexible Anpassung an unterschiedliche Signalbereiche ohne Änderung des Bausteins selbst.