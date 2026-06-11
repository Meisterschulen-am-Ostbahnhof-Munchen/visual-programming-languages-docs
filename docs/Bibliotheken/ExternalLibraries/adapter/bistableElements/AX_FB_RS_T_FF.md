# AX_FB_RS_T_FF


![AX_FB_RS_T_FF](./AX_FB_RS_T_FF.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AX_FB_RS_T_FF** realisiert ein rücksetzdominantes bistabiles Kippglied (Reset-Dominant Latch) mit zusätzlicher Toggle-Funktion. Der Baustein kommuniziert über standardisierte Adapter-Schnittstellen und ermöglicht eine flexible Anbindung an andere Komponenten.

## Schnittstellenstruktur

Der Baustein besitzt keine direkten Ereignis- oder Dateneingänge/-ausgänge auf FB-Ebene. Die gesamte Kommunikation erfolgt über **Adapter**, die wiederum eigene Ereignis- und Datenkanäle bereitstellen.

### **Ereignis-Eingänge**

Die folgenden Adapter-Ereignisse lösen die Verarbeitung aus:

- **SET.E1** – Ereignis zum Setzen des Ausgangs
- **RESET1.E1** – Ereignis zum Zurücksetzen des Ausgangs (Priorität)
- **CLK.E1** – Ereignis für den Takt, der bei steigender Flanke einen Toggle auslöst

### **Ereignis-Ausgänge**

- **Q1.E1** – Ereignis, das nach jeder Ausführung des Algorithmus gesendet wird (unabhängig vom Ergebnis)

### **Daten-Eingänge**

Über die Adapter werden folgende Datenwerte empfangen:

- **SET.D1** (BOOL) – Setz-Eingang: `TRUE` → setzt Q1 auf `TRUE`
- **RESET1.D1** (BOOL) – Reset-Eingang: `TRUE` → setzt Q1 auf `FALSE` (hat Priorität vor SET)
- **CLK.D1** (BOOL) – Takteingang: Flankenwechsel von `FALSE` nach `TRUE` löst Toggle aus

### **Daten-Ausgänge**

- **Q1.D1** (BOOL) – Ausgangswert des Flipflops

### **Adapter**

| Adapter | Typ | Rolle | Kommentar |
|--------|------|-------|-----------|
| `SET` | adapter::types::unidirectional::AX | Eingang | Setzen |
| `RESET1` | adapter::types::unidirectional::AX | Eingang | Zurücksetzen |
| `CLK` | adapter::types::unidirectional::AX | Eingang | Takt |
| `Q1` | adapter::types::unidirectional::AX | Ausgang | Ausgabe |

Alle Adapter sind vom Typ `AX` (unidirektional) und stellen jeweils einen Ereigniskanal (`.E1`) sowie einen Datenkanal (`.D1`) zur Verfügung.

## Funktionsweise

Der Baustein arbeitet nach folgendem deterministischen Algorithmus, der bei jedem eingehenden Ereignis (SET, RESET1 oder CLK) ausgeführt wird:

1. **Priorität: Reset dominierend**  
   Ist `RESET1.D1 = TRUE`, wird `Q1.D1` auf `FALSE` gesetzt.

2. **Andernfalls: Set Vorrang**  
   Ist nur `SET.D1 = TRUE` (und `RESET1.D1 = FALSE`), wird `Q1.D1` auf `TRUE` gesetzt.

3. **Sonst: Toggle bei steigender Flanke**  
   Liegen weder RESET1 noch SET an, wird geprüft, ob `CLK.D1 = TRUE` und im vorherigen Zyklus `FALSE` war (steigende Flanke). In diesem Fall wird der Ausgang `Q1` invertiert (`NOT Q1.D1`).

4. **Flankenerkennung**  
   Die interne Variable `EDGE` speichert den letzten Wert von `CLK.D1`. Nach jedem Durchlauf wird sie aktualisiert (`EDGE := CLK.D1`). Dadurch wird die steigende Flanke erkannt, sobald `CLK.D1` von `FALSE` auf `TRUE` wechselt.

Nach der Ausführung des Algorithmus wird stets das Ereignis `Q1.E1` gesendet.

## Technische Besonderheiten

- **Adapterbasierte Kommunikation**: Der Baustein verwendet ausschließlich Adapter für Ein- und Ausgabe, was eine lose Kopplung und Wiederverwendbarkeit in unterschiedlichen Kontexten erleichtert.
- **Rücksetzdominanz**: Der Reset-Eingang hat Vorrang vor dem Set-Eingang. Dies entspricht dem typischen Verhalten eines RS-Flipflops mit Priorität für den Reset.
- **Flankengetriggerter Toggle**: Das Toggle erfolgt nur bei einer steigenden Flanke des Taktsignals, nicht bei statischem High-Pegel. Die interne Flankenerkennung verhindert mehrfaches Umschalten bei anhaltendem `TRUE` am Takt.
- **Ein-Zustands-ECC**: Der Funktionsbaustein besitzt nur einen Zustand (`REQ`). Alle Transitionen führen zurück zu diesem Zustand, was einer kontinuierlichen Verarbeitung jedes eingehenden Ereignisses ohne zusätzliche Zustandslogik entspricht.

## Zustandsübersicht

Der Baustein ist als **Basic FB** mit folgendem ECC realisiert:

| Zustand | Aktion | Ausgabe |
|---------|--------|---------|
| `REQ` | Führe Algorithmus `REQ` aus | `Q1.E1` (nach Algorithmus) |

Übergänge:

- Von `REQ` nach `REQ` bei **RESET1.E1**
- Von `REQ` nach `REQ` bei **SET.E1**
- Von `REQ` nach `REQ` bei **CLK.E1**

Es gibt keine weiteren Zustände. Der Algorithmus wird immer im gleichen Kontext ausgeführt.

## Anwendungsszenarien

- **Sicherheitssteuerungen**: Ein rücksetzdominantes Verhalten ist nützlich, wenn ein Fehlerzustand (Reset) höchste Priorität haben muss, z.B. in Not-Aus-Schaltungen.
- **Toggle-Funktion mit Takt**: Umschalten zwischen zwei Zuständen bei jedem Taktimpuls, z.B. für Blinklicht oder Impulszähler.
- **Hybride Schaltungen**: Kombination aus Set/Reset und Umschaltfunktion in einer Komponente, was Platz und Logik spart.

## Vergleich mit ähnlichen Bausteinen

- **RS-Flipflop (reset-dominant)**: Verhält sich wie ein herkömmliches RS-Flipflop mit Reset-Vorrang, bietet aber keinen Toggle.
- **T-Flipflop**: Kann nur toggeln, besitzt keine separaten Set-/Reset-Eingänge.
- **JK-Flipflop**: Bietet Set, Reset und Toggle, jedoch mit anderer Prioritätslogik (kein expliziter Reset-Dominanz).
- **AX_FB_RS_T_FF** vereint Reset-Dominanz und Flanken-getriggerten Toggle in einem Baustein, nutzt Adapter für plattformunabhängige Anbindung.

## Fazit

Der **AX_FB_RS_T_FF** ist ein vielseitiger, adapterbasierter Funktionsbaustein für bistabile Schaltungen mit rücksetzdominanter Logik und integrierter Toggle-Funktion. Durch die Verwendung von Adaptern lässt er sich einfach in modulare Automatisierungssysteme integrieren. Die Flankenerkennung und die klare Priorität der Eingänge machen ihn robust und zuverlässig für typische Steuerungsaufgaben.