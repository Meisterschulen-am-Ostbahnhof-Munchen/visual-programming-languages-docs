# AUS_TO_AD


![AUS_TO_AD](./AUS_TO_AD.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AUS_TO_AD** ist ein Composite-Baustein, der eine einfache Konvertierung von einem USINT-Adapter (Typ AUS) zu einem DWORD-Adapter (Typ AD) durchführt.  
Er kapselt die Umwandlung eines vorzeichenlosen 8‑Bit‑Wertes (USINT) in einen 32‑Bit‑DWORD‑Wert und macht diese über standardisierte Adapter‑Schnittstellen zugänglich.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `E1` | Ereignis (vom Socket `AUS_IN`) | Startet die Konvertierung des anliegenden USINT‑Wertes. Der Eingang wird über den Socket `AUS_IN` bereitgestellt. |

### **Ereignis-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `E1` | Ereignis (zum Plug `AD_OUT`) | Signalisiert die erfolgreiche Konvertierung und das Vorliegen des DWORD‑Wertes am Ausgang. Der Ausgang wird über den Plug `AD_OUT` bereitgestellt. |

### **Daten-Eingänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `D1` | USINT (vom Socket `AUS_IN`) | Der zu konvertierende 8‑Bit‑Wert im Bereich 0…255. |

### **Daten-Ausgänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `D1` | DWORD (zum Plug `AD_OUT`) | Der konvertierte 32‑Bit‑Wert (direkte Typumsetzung des USINT in DWORD). |

### **Adapter**

| Rolle | Name | Typ | Richtung | Beschreibung |
|-------|------|-----|----------|--------------|
| Socket | `AUS_IN` | `adapter::types::unidirectional::AUS` | Eingang | Nimmt den USINT‑Wert sowie das zugehörige Ereignis entgegen. |
| Plug   | `AD_OUT` | `adapter::types::unidirectional::AD`   | Ausgang | Stellt den DWORD‑Wert sowie das Bestätigungsereignis bereit. |

## Funktionsweise

Der Baustein implementiert eine einfache, durchgängige Datenkonvertierung:

1. Ein eingehendes Ereignis am Adapter‑Eingang `AUS_IN.E1` triggert die interne Konvertierung.
2. Der angeschlossene USINT‑Wert (`AUS_IN.D1`) wird über den standardisierten IEC‑61131‑Funktionsbaustein `F_USINT_TO_DWORD` in einen DWORD‑Wert umgewandelt.
3. Nach erfolgreicher Konvertierung wird das Ausgangsereignis `AD_OUT.E1` gesendet und der DWORD‑Wert unter `AD_OUT.D1` bereitgestellt.

Der Baustein arbeit ohne eigene Zustandslogik – er führt die Konvertierung pro Ereignis sofort aus (transparentes Verhalten).

## Technische Besonderheiten

- **Composite‑Bauweise:** Der Baustein besteht ausschließlich aus einem internen Netzwerk mit einem einzelnen Funktionsbaustein (`F_USINT_TO_DWORD`) sowie direkten Ereignis‑ und Datenverbindungen.
- **Wiederverwendung:** Die Konvertierung nutzt die IEC‑61131‑3‑Standardfunktion `F_USINT_TO_DWORD`, die in der Bibliothek `iec61131::conversion` enthalten ist.
- **Adapter‑Schnittstellen:** Die Schnittstellen sind als unidirektionale Adapter (`adapter::types::unidirectional::AUS` bzw. `AD`) realisiert. Jeder Adapter besteht aus genau einem Ereignis‑ und einem Datenkanal.
- **Kein Zustandsautomat:** Da es sich um einen reinen Composite‑Baustein ohne eigenen ECC handelt, werden keine Zustände verwaltet.

## Zustandsübersicht

Der Baustein besitzt keine eigene Zustandsmaschine. Das Verhalten ist rein datenflussgesteuert: Bei jedem eingehenden Ereignis wird genau eine Konvertierung durchgeführt und das Ereignis unverzögert weitergeleitet.

## Anwendungsszenarien

- **Schnittstellenanpassung:** Wenn ein USINT‑Wert (z. B. ein Byte‑Sensor) in einem System genutzt werden muss, das intern nur DWORD‑Werte verarbeitet.
- **Adapter‑Brückenbildung:** Einsatz in modularen Steuerungsarchitekturen, in denen Adapter‑Typen nicht direkt kompatibel sind und eine Konvertierung zwischen AUS‑ und AD‑Adaptern erforderlich ist.
- **Prototyp‑/Testumgebungen:** Schnelle Verbindung zweier Komponenten mit unterschiedlichen Adapter‑Definitionen ohne eigene Konvertierungslogik.

## Vergleich mit ähnlichen Bausteinen

- **F_USINT_TO_DWORD:** Der zugrunde liegende Konvertierungsbaustein ist ein reiner Datenkonverter ohne Adapter‑Schnittstelle. Er setzt direkte Daten‑ und Ereignisverbindungen voraus.  
  `AUS_TO_AD` hingegen kapselt diese Funktion und bietet eine standardisierte Adapter‑Schnittstelle an.

- **Andere Adapter‑Konverter (z. B. BYTE_TO_DWORD, WORD_TO_DWORD):** Ähnliche Bausteine existieren für andere Datentypen, setzen aber meist andere Adapter‑Typen voraus. `AUS_TO_AD` ist speziell für die Kombination der Adapter `AUS` (USINT) und `AD` (DWORD) optimiert.

## Fazit

Der Funktionsbaustein `AUS_TO_AD` bietet eine einfache und robuste Möglichkeit, einen unidirektionalen USINT‑Adapter in einen DWORD‑Adapter umzuwandeln. Durch die Verwendung des standardisierten Konvertierungsbausteins und der Adapter‑Schnittstellen lässt er sich nahtlos in IEC‑61499‑basierten Automatisierungssystemen einsetzen. Er reduziert den manuellen Aufwand für Typkonvertierungen und sorgt für eine saubere, wiederverwendbare Schnittstellenanpassung.