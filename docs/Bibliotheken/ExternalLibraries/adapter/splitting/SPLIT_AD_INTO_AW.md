# SPLIT_AD_INTO_AW


![SPLIT_AD_INTO_AW](./SPLIT_AD_INTO_AW.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **SPLIT_AD_INTO_AW** dient dazu, einen 32‑Bit‑DWORD‑Wert, der über einen **AD**‑Adapter (Unidirectional) anliegt, in zwei 16‑Bit‑WORD‑Werte aufzuteilen und diese über zwei separate **AW**‑Adapter (Unidirectional) auszugeben. Die Aufteilung erfolgt ereignisgesteuert, und die Ausgabedaten werden durch Flip‑Flops stabil gehalten, bis ein neuer Trigger eintrifft. Der Baustein ist als zusammengesetzter FB (Composite) realisiert und nutzt intern den Baustein **SPLIT_DWORD_INTO_WORDS** sowie zwei **E_D_FF_ANY**‑Flip‑Flops.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Bezeichnung | Adapter | Ereignis | Beschreibung |
|-------------|---------|----------|--------------|
| IN          | AD (Socket) | E1 | Startet die Aufteilung des anliegenden DWORD‑Wertes. |

### **Ereignis-Ausgänge**

| Bezeichnung | Adapter | Ereignis | Beschreibung |
|-------------|---------|----------|--------------|
| WORD_00     | AW (Plug) | E1 | Signalisiert, dass das niederwertige WORD (Low‑Word) gültig ist. |
| WORD_01     | AW (Plug) | E1 | Signalisiert, dass das höherwertige WORD (High‑Word) gültig ist. |

### **Daten-Eingänge**

| Bezeichnung | Adapter | Datentyp | Beschreibung |
|-------------|---------|----------|--------------|
| IN          | AD (Socket) | D1 (DWORD) | 32‑Bit‑Eingangswert, der aufgeteilt wird. |

### **Daten-Ausgänge**

| Bezeichnung | Adapter | Datentyp | Beschreibung |
|-------------|---------|----------|--------------|
| WORD_00     | AW (Plug) | D1 (WORD) | Niederwertiges 16‑Bit‑Wort des Eingangs‑DWORD. |
| WORD_01     | AW (Plug) | D1 (WORD) | Höherwertiges 16‑Bit‑Wort des Eingangs‑DWORD. |

### **Adapter**

Die Adapter sind als **unidirectional** ausgelegt:
- **AD** (Eingang): Über einen Socket bereitgestellt, enthält je einen Ereignis‑ (E1) und Daten‑ (D1) Kanal.
- **AW** (Ausgang): Über zwei Plugs bereitgestellt, jeweils mit einem Ereignis‑ (E1) und Daten‑ (D1) Kanal.

## Funktionsweise

1. Ein Ereignis am Eingang **IN.E1** triggert die Verarbeitung.
2. Der aktuelle DWORD‑Wert von **IN.D1** wird gelesen und an den internen Baustein **SPLIT_DWORD_INTO_WORDS** weitergeleitet.
3. Dieser teilt den 32‑Bit‑Wert in zwei 16‑Bit‑Wörter: **WORD_00** (niederwertig) und **WORD_01** (höherwertig).
4. Die beiden Ergebnisse werden parallel in die Flip‑Flops **E_D_FF_ANY_00** und **E_D_FF_ANY_01** übernommen und dort bis zum nächsten Ereignis gehalten.
5. Gleichzeitig werden die Ausgangs‑Ereignisse **WORD_00.E1** und **WORD_01.E1** ausgelöst, die anzeigen, dass die entsprechenden Daten (**WORD_00.D1** und **WORD_01.D1**) gültig sind.

## Technische Besonderheiten

- **Datensynchronisation:** Durch die Flip‑Flops bleiben die Ausgangsdaten stabil, auch wenn der Eingangswert zwischen zwei Ereignissen wechselt. Erst ein neues Ereignis am Eingang aktualisiert beide Ausgänge.
- **Gleichzeitige Ausgabe:** Beide WORD‑Ausgänge werden durch dasselbe Eingangsereignis aktualisiert – es gibt keine zeitliche Staffelung.
- **Adapter‑Konformität:** Der FB ist speziell für die Verwendung mit **AD‑** und **AW‑** Adaptern ausgelegt und erlaubt eine nahtlose Einbindung in adapterbasierte Datenflüsse.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten. Das Verhalten ist rein ereignisgesteuert:
- **Idle:** Warten auf ein Ereignis an **IN.E1**.
- **Verarbeitung:** Bei Eintreffen von **IN.E1** wird die Aufteilung durchgeführt und die Flip‑Flops gesetzt.
- **Ausgabe:** Die Ereignisse an den Ausgängen werden genau einmal nach der Verarbeitung ausgelöst.

## Anwendungsszenarien

- **Adapter‑basierte Zerlegung:** Trennen einer 32‑Bit‑Größe (z. B. aus einem Sensor‑Datenwort) in zwei 16‑Bit‑Teile für getrennte Verarbeitungsketten.
- **Kommunikationsprotokolle:** Aufbereitung von Daten für Schnittstellen, die WORD‑weise übertragen (z. B. Modbus‑Register oder CAN‑Nachrichten).
- **Bit‑Manipulation:** Vorverarbeitung für nachfolgende Bausteine, die nur WORD‑Adapter erwarten.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Beschreibung | Unterschied |
|----------|--------------|-------------|
| **SPLIT_DWORD_INTO_WORDS** | Reine Datenaufteilung ohne Ereignisausgabe oder Adapter. | Liefert nur Datenausgänge, keine Ereignisse und keine Adapter‑Anbindung. |
| **SPLIT_AD_INTO_AW** | Adapter‑basierte Variante mit stabilisierten Ausgängen. | Integriert Flip‑Flops und Ereignisausgabe, speziell für AD‑/AW‑Adapter. |

## Fazit

**SPLIT_AD_INTO_AW** ist ein praktischer zusammengesetzter Funktionsblock, der die Aufteilung eines DWORD‑Adapter‑Signals in zwei WORD‑Adapter‑Signale vereinfacht. Durch die eingebauten Flip‑Flops und die synchronisierte Ereignisausgabe eignet er sich besonders für zeitkritische und adapterorientierte Anwendungen in industriellen Steuerungen.