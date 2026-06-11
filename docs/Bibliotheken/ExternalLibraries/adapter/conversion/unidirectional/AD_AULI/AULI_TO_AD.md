# AULI_TO_AD


![AULI_TO_AD](./AULI_TO_AD.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AULI_TO_AD** ist ein Composite-Baustein, der einen unidirektionalen Adapter vom Typ **AULI** (ULINT) in einen unidirektionalen Adapter vom Typ **AD** (DWORD) umwandelt. Er dient als Brücke zwischen Komponenten, die Daten im ULINT-Format bereitstellen, und solchen, die ein DWORD-Format erwarten. Die Umwandlung erfolgt mithilfe der IEC 61131‑Funktion `F_ULINT_TO_DWORD`.

## Schnittstellenstruktur

Der Baustein besitzt keine eigenen Ereignis- oder Datenein‑/ausgänge, sondern kommuniziert ausschließlich über zwei Adapter:

### **Ereignis-Eingänge**

| Adapter   | Ereignis | Beschreibung                     |
|-----------|----------|----------------------------------|
| `AULI_IN` | `E1`     | Startet die Konvertierung        |

### **Ereignis-Ausgänge**

| Adapter   | Ereignis | Beschreibung                     |
|-----------|----------|----------------------------------|
| `AD_OUT`  | `E1`     | Signalisiert abgeschlossene Konvertierung |

### **Daten-Eingänge**

| Adapter   | Variable | Datentyp | Beschreibung                     |
|-----------|----------|----------|----------------------------------|
| `AULI_IN` | `D1`     | ULINT    | Eingangswert für die Umwandlung  |

### **Daten-Ausgänge**

| Adapter   | Variable | Datentyp | Beschreibung                     |
|-----------|----------|----------|----------------------------------|
| `AD_OUT`  | `D1`     | DWORD    | Konvertierter Ausgangswert       |

### **Adapter**

| Name       | Richtung | Typ                                       | Beschreibung               |
|------------|----------|-------------------------------------------|----------------------------|
| `AULI_IN`  | Socket   | `adapter::types::unidirectional::AULI`    | Eingangsadapter (ULINT)    |
| `AD_OUT`   | Plug     | `adapter::types::unidirectional::AD`      | Ausgangsadapter (DWORD)    |

## Funktionsweise

Der Baustein verbindet intern den Socket `AULI_IN` mit dem Funktionsbaustein `F_ULINT_TO_DWORD` und dessen Ausgang mit dem Plug `AD_OUT`. Die Ablaufsteuerung erfolgt über Ereignisse:

1. Ein eingehendes Ereignis an `AULI_IN.E1` aktiviert den Eingang der Konvertierungsfunktion.
2. Der Datenwert `AULI_IN.D1` (ULINT) wird an den Eingang `IN` der Funktion übergeben.
3. Nach der Umwandlung wird das Ergebnis (DWORD) am Ausgang `OUT` bereitgestellt.
4. Gleichzeitig wird ein Ereignis an `AD_OUT.E1` ausgegeben, um den angeschlossenen Baustein über die neuen Daten zu informieren.

Der gesamte Vorgang ist ereignisgesteuert und erfolgt ohne jegliche Verzögerung oder Zustandsspeicherung.

## Technische Besonderheiten

- **Composite‑Struktur**: Der Baustein ist als Netzwerk aus einem einzigen Funktionsbaustein (`F_ULINT_TO_DWORD`) realisiert. Alle Verbindungen sind fest verdrahtet.
- **Paket‑Import**: Die verwendete Konvertierungsfunktion stammt aus dem Paket `iec61131::conversion`. Der Baustein ist im Paket `adapter::conversion::unidirectional` organisiert.
- **Keine Zustandshaltung**: Der Baustein ist rein kombinatorisch – jedes Eingangsereignis erzeugt sofort ein Ausgangsereignis mit dem umgewandelten Wert.
- **Typsicherheit**: Die Adapter‑Schnittstellen sind strikt auf ULINT bzw. DWORD festgelegt, sodass Fehlverbindungen bereits zur Entwicklungszeit erkannt werden.

## Zustandsübersicht

Da es sich um einen Composite‑Baustein ohne eigene Algorithmen handelt, existiert keine explizite Zustandsmaschine. Der Gesamtzustand ergibt sich ausschließlich aus dem internen Zustand des verwendeten Funktionsbausteins `F_ULINT_TO_DWORD`, der nach jedem Ausführungszyklus in den Ruhezustand zurückkehrt. Im Normalbetrieb wechselt der Baustein zwischen:

- **Warten**: Auf ein Ereignis an `AULI_IN.E1`.
- **Konvertieren**: Kurze Ausführung von `F_ULINT_TO_DWORD`.
- **Ausgeben**: Senden des Ergebnisses und des Ereignisses an `AD_OUT.E1`.

## Anwendungsszenarien

- **Datenanpassung in der Landtechnik**: Umwandlung von ULINT‑Werten (z. B. von Sensoren oder Steuergeräten) in das von nachgelagerten Komponenten geforderte DWORD‑Format.
- **Adapter‑basierte Kommunikation**: Einsatz in Modulen, die ausschließlich über Adapter‑Schnittstellen miteinander verbunden werden, ohne direkte Ein‑/Ausgangspins.
- **Systemintegration**: Wenn ein bestehendes System ULINT‑Daten liefert, ein anderes aber nur DWORD‑Adapter akzeptiert, dient dieser Baustein als einfacher Konverter.

## Vergleich mit ähnlichen Bausteinen

| Baustein        | Beschreibung                                                                 |
|-----------------|------------------------------------------------------------------------------|
| `F_ULINT_TO_DWORD` | Einfache Konvertierungsfunktion, jedoch ohne Adapter‑Einbindung.          |
| `AULI_TO_AD`    | Gleiche Funktionalität, aber als Composite‑Baustein mit Adapter‑Schnittstellen. |
| Andere Adapter‑Konverter | Es existieren Bausteine für verwandte Typen (z. B. LINT, DINT), die nach demselben Prinzip arbeiten. |

Der wesentliche Unterschied liegt in der Schnittstellenart: Während die reine Funktion direkte Daten‑ und Ereignispins verwendet, kapselt `AULI_TO_AD` die Konvertierung in eine adapterbasierte Lösung.

## Fazit

Der Funktionsblock `AULI_TO_AD` bietet eine saubere, standardisierte Möglichkeit, ULINT‑Daten über einen AULI‑Adapter in das DWORD‑Format eines AD‑Adapters zu überführen. Dank seiner Composite‑Natur ist er einfach einsetzbar, erfordert keine eigene Programmierung und fügt sich nahtlos in eine adapterorientierte Architektur ein. Er ist besonders nützlich in Umgebungen, in denen Komponenten über definierte Adapter‑Schnittstellen kommunizieren.