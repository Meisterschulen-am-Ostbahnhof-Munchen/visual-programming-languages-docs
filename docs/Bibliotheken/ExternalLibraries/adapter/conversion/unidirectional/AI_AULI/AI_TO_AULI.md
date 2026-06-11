# AI_TO_AULI


![AI_TO_AULI](./AI_TO_AULI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AI_TO_AULI** dient als Composite-Baustein zur Konvertierung eines unidirektionalen Adapters vom Typ `AI` (basierend auf dem Datentyp `INT`) in einen unidirektionalen Adapter vom Typ `AULI` (basierend auf `ULINT`). Er ermöglicht die nahtlose Integration von Komponenten, die unterschiedliche ganzzahlige Datentypen verwenden, ohne dass der Anwender die Konvertierungslogik selbst implementieren muss.

---

## Schnittstellenstruktur

Der Baustein besitzt keine klassischen Ereignis- oder Datenein-/ausgänge, sondern ausschließlich Adapter-Schnittstellen (Socket & Plug), über die sowohl Ereignisse als auch Daten übertragen werden.

### **Ereignis-Eingänge**

Der Ereigniseingang wird über den Socket-Adapter `AI_IN` bereitgestellt.

| Name   | Adapter | Kommentar                           |
|--------|---------|-------------------------------------|
| `E1`   | `AI_IN` | Ereignis, das die Konvertierung auslöst |

### **Ereignis-Ausgänge**

Der Ereignisausgang wird über den Plug-Adapter `AULI_OUT` bereitgestellt.

| Name   | Adapter   | Kommentar                              |
|--------|-----------|----------------------------------------|
| `E1`   | `AULI_OUT`| Ereignis nach erfolgreicher Konvertierung |

### **Daten-Eingänge**

Der Dateneingang wird über den Socket-Adapter `AI_IN` bereitgestellt.

| Name   | Adapter | Typ  | Kommentar               |
|--------|---------|------|-------------------------|
| `D1`   | `AI_IN` | `INT`| Eingangsdaten (16‑Bit Integer) |

### **Daten-Ausgänge**

Der Datenausgang wird über den Plug-Adapter `AULI_OUT` bereitgestellt.

| Name   | Adapter   | Typ    | Kommentar                |
|--------|-----------|--------|--------------------------|
| `D1`   | `AULI_OUT`| `ULINT`| Ausgangsdaten (64‑Bit vorzeichenloser Integer) |

### **Adapter**

- **Socket** `AI_IN` : Unidirektionaler Adapter mit den Schnittstellen `E1` (Ereignis) und `D1` (INT).
- **Plug** `AULI_OUT` : Unidirektionaler Adapter mit den Schnittstellen `E1` (Ereignis) und `D1` (ULINT).

---

## Funktionsweise

Der Baustein realisiert eine einfache Typkonvertierung von `INT` nach `ULINT`. Intern wird der IEC 61131‑Baustein `F_INT_TO_ULINT` verwendet. Die Ablaufsteuerung erfolgt ereignisgesteuert:

1. Ein eingehendes Ereignis am Socket `AI_IN.E1` triggert den Eingang `REQ` des Konvertierungsbausteins.
2. Der Datenwert `AI_IN.D1` (INT) wird an den Eingang `IN` des Konvertierungsbausteins übergeben.
3. Die Konvertierung wird ausgeführt und das Ergebnis (ULINT) am Ausgang `OUT` bereitgestellt.
4. Nach Abschluss der Konvertierung wird ein Ereignis am Ausgang `CNF` des Konvertierungsbausteins generiert, das an den Plug `AULI_OUT.E1` weitergeleitet wird.
5. Parallel dazu wird der konvertierte Wert an den Plug `AULI_OUT.D1` gesendet.

Dadurch wird eine vollständige, synchronisierte Übertragung von Ereignis und Daten gewährleistet.

---

## Technische Besonderheiten

- **Adapterbasierte Kommunikation:** Der Baustein kapselt die Konvertierungslogik in einem Composite, sodass die angeschlossenen Komponenten nur die jeweiligen Adapter-Schnittstellen kennen müssen.
- **Unidirektionaler Datentransfer:** Sowohl `AI` als auch `AULI` sind als unidirektionale Adapter ausgelegt; eine Rückrichtung ist nicht vorgesehen.
- **Typkonvertierung:** Der interne Baustein `F_INT_TO_ULINT` führt eine erweiternde Umwandlung von 16‑Bit Integer (`INT`) zu 64‑Bit vorzeichenlosem Integer (`ULINT`) durch. Negative `INT`‑Werte werden dabei gemäß dem Zweierkomplement in große positive `ULINT`‑Werte umgewandelt (z. B. `-1` → `2^64-1`).
- **Keine Eigenzustände:** Der Baustein besitzt keine eigene Zustandsmaschine, sondern leitet Ereignisse und Daten direkt weiter.

---

## Zustandsübersicht

Da der Baustein als reines Composite ohne eigene zustandsbehaftete Logik realisiert ist, existiert keine explizite Zustandsmaschine. Das Verhalten wird allein durch die Kopplung der internen Bausteine bestimmt. Die Funktionalität ist rein kombinatorisch und ereignisgetriggert.

---

## Anwendungsszenarien

- **Adapter‑Wandler:** Einbinden von Sensoren oder Aktoren, die als `AI`‑Adapter (INT) bereitgestellt werden, in ein System, das `AULI`‑Adapter (ULINT) erwartet.
- **Systemintegration:** Verwenden in SPS‑ oder Automatisierungsarchitekturen, in denen unterschiedliche Datentypen normiert werden müssen.
- **Protokollanpassung:** Konvertieren von 16‑Bit Zählerwerten in 64‑Bit Zählerwerte für erweiterte Reichweite.

---

## Vergleich mit ähnlichen Bausteinen

| Baustein          | Quelltyp | Zieltyp | Adapterbasiert | Eigene Zustände |
|-------------------|----------|---------|----------------|-----------------|
| `F_INT_TO_ULINT`  | `INT`    | `ULINT` | Nein (reine FB) | Nein            |
| `AI_TO_AULI`      | `AI`     | `AULI`  | Ja (Adapter)   | Nein            |
| `ANY_TO_ANY`      | variabel | variabel| möglich        | je nach Implementierung |

Während der Basisbaustein `F_INT_TO_ULINT` nur die Datenkonvertierung vornimmt, kapselt `AI_TO_AULI` diese zusammen mit der Ereignissteuerung in einer adapterkompatiblen Schnittstelle. Dadurch wird die Wiederverwendbarkeit in adapterbasierten Systemen erhöht.

---

## Fazit

Der Funktionsblock `AI_TO_AULI` bietet eine saubere, adapterbasierte Lösung zur Konvertierung von `INT`‑ nach `ULINT`‑Daten. Er reduziert den manuellen Aufwand und die Fehleranfälligkeit bei der Typanpassung und lässt sich nahtlos in bestehende 4diac‑Projekte integrieren. Dank seiner einfachen, ereignisgetriggerten Struktur ist er besonders für unidirektionale Datenflüsse geeignet.