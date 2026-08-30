# E_TMIN

* * * * * * * * * *

## Einleitung

Der `E_TMIN` (Minimum inter-arrival time) ist ein Composite-Funktionsbaustein, der eingehende Ereignisse an `EI` nur dann an `EO` weiterleitet, wenn seit dem letzten weitergeleiteten Ereignis mindestens die Zeitspanne `Tmin` vergangen ist. Er dient als Ereignis-Drossel (Rate-Limiter) für beliebige Ereignisströme.

![E_TMIN](E_TMIN.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Initialisierung, trägt `Tmin`.
- **EI**: Eingehendes, zu drosselndes Ereignis.

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt die Initialisierung.
- **EO**: Das gedrosselte Ausgangsereignis.

### **Daten-Eingänge**

- **Tmin** (TIME): Mindestabstand zwischen zwei aufeinanderfolgenden `EI`-Ereignissen, die tatsächlich zu `EO` führen.

## Funktionsweise

Intern verwendet `E_TMIN` einen `E_REND` (Rendezvous zweier Ereignisse) und einen `E_DELAY`: Trifft `EI` ein, wird es an `E_REND.EI1` weitergegeben. `E_REND` feuert seinerseits `EO`, sobald es sowohl an `EI1` als auch an `EI2` mindestens ein Ereignis erhalten hat — zu Beginn ist `EI2` bereits durch `INIT` "vorbelegt", sodass das erste `EI` sofort durchgereicht wird. Jedes von `E_REND` durchgelassene Ereignis startet gleichzeitig den `E_DELAY` mit der Zeit `Tmin`; erst wenn dieser abläuft, liefert er das nächste `EI2`-Ereignis an `E_REND`, wodurch der nächste `EI`-Durchlass frühestens nach `Tmin` möglich wird.

## Technische Besonderheiten

- **Baustein aus zwei Standardelementen**: `E_TMIN` ist eine reine Verdrahtung aus `E_REND` und `E_DELAY`, ohne eigene ECC.
- **Erstes Ereignis unverzögert**: Das erste `EI` nach `INIT` wird sofort durchgelassen; die Drosselung setzt erst danach ein.
- **Baustein für die `_TMIN`-Familie**: Wird intern von [E_D_FF_TMIN](E_D_FF_TMIN.md) und [E_D_FF_ANY_TMIN](E_D_FF_ANY_TMIN.md) verwendet, um deren `EO`-Ausgänge zusätzlich zu drosseln.

## Zustandsübersicht

Zustandslose Verdrahtungslogik: `E_REND` speichert intern, ob bereits ein `EI2` (vom `E_DELAY`) eingetroffen ist, `E_DELAY` läuft nach jedem durchgelassenen Ereignis erneut an.

## Anwendungsszenarien

- **Drosselung schnell wechselnder Sensorereignisse**, um nachgeschaltete Logik (z. B. Logging, Netzwerkversand) nicht mit einer zu hohen Ereignisrate zu überlasten.
- **Baustein innerhalb von [E_D_FF_TMIN](E_D_FF_TMIN.md)/[E_D_FF_ANY_TMIN](E_D_FF_ANY_TMIN.md)**, um Änderungsereignisse zusätzlich zeitlich zu begrenzen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`E_REND`**: die intern verwendete Synchronisationsbasis, ohne Zeitkomponente.
- **`E_DELAY`**: der intern verwendete Timer.
- **[E_D_FF_TMIN](E_D_FF_TMIN.md) / [E_D_FF_ANY_TMIN](E_D_FF_ANY_TMIN.md)**: kombinieren `E_TMIN` zusätzlich mit einem Daten-Latch (`E_D_FF`/`E_D_FF_ANY`).

## Fazit

`E_TMIN` ist ein einfacher, aber wirkungsvoller Ereignis-Drosselbaustein, der aus zwei Standardelementen (`E_REND`, `E_DELAY`) zusammengesetzt ist und eine Mindestabstandszeit zwischen durchgelassenen Ereignissen garantiert.
